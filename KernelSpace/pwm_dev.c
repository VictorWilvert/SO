#include <linux/module.h>   		/* Necessario para todos modulos */
#include <linux/kernel.h>   		/* Necessario para KERN_INFO */
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/sysfs.h>
#include <linux/interrupt.h> 
#include <linux/gpio.h>
#include <asm/io.h>
#include <linux/platform_device.h>

#define CLASS_NAME "pwm_device"
/* enderecos usadas, tirados o datashet */
#define BCM2837_PERI_BASE				0x3F000000
#define GPIO_BASE					(BCM2837_PERI_BASE + 0x200000)
#define PWM_BASE 					(BCM2837_PERI_BASE + 0x20C000)
#define CLOCK_BASE					(BCM2837_PERI_BASE + 0x101000)
/* variaveis globais */
static DEFINE_MUTEX(sysfs_lock);
static void __iomem *pwm_reg;
static void __iomem *gpio_reg;
static void __iomem *clk_reg;
/* macro para escrita no registrador das GPIOs */
#define GPIO_REG(g) (gpio_reg+((g/10)*4))
/* macro para alteracao da funcao das GPIOs */
#define SET_GPIO_ALT(g,a) 										\
		__raw_writel(											\
			(((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))			\
			| (__raw_readl(GPIO_REG(g)) & (~(7<<(((g)%10)*3)))),\
			GPIO_REG(g))
/* macros para escrita nos registradores do PWM */
#define	PWM_CTL  					(pwm_reg+(0*4))
#define	PWM_RNG1 					(pwm_reg+(4*4))
#define	PWM_DAT1 					(pwm_reg+(5*4))
#define	PWMCLK_CNTL 					(clk_reg+(40*4))
#define	PWMCLK_DIV  					(clk_reg+(41*4))

struct pwm_device {
	u32 duty;
	u32 frequency;
	int active:1;
	int immediate:1;
	int loaded:1;
	struct device *dev;
	u32 divisor;		
	u32 mcf; 			/* frequencia maxima comum / limite */
} pwm;

static int pwm_set_clk(struct pwm_device *dev) {
	/* Mata o clock do PWM */
	__raw_writel(0x5A000020,PWMCLK_CNTL);
	udelay(10);  
	/* Define a frequencia */
	dev->divisor = 19200000 / dev->mcf;
	if (dev->divisor < 1 || dev->divisor > 0x1000) {
		dev_err(dev->dev, "divisor out of range: %x\n", dev->divisor);
		return -ERANGE;
	}
	__raw_writel(0x5A000000 | (dev->divisor<<12), PWMCLK_DIV);
	udelay(10);
	/* Habilita o clock do PWM*/
	__raw_writel(0x5A000011, PWMCLK_CNTL);
	udelay(10);
	return 0;
}

static int pwm_activate(struct pwm_device *dev) {
	ssize_t ret = 0;
	unsigned long RNG, DAT;
	/* Defini a funcao alternativa para a GPIO18 */
	printk(KERN_INFO "PWM: pwm_activate...");
	SET_GPIO_ALT(18,0);
	udelay(10);
	SET_GPIO_ALT(18,5);
	udelay(10);
	/* Disabilita o PWM */
	__raw_writel(0, PWM_CTL);
	udelay(10);
	/* Define o clock do PWM */
	ret = pwm_set_clk(dev);
	if (ret) {
		return ret;
	}
	/* Definicao do duty cycle do PWM */
	RNG = dev->mcf/dev->frequency;
	/**/
	DAT = RNG*dev->duty/100;
	if (RNG < 1) {
		dev_err(dev->dev, "RNG is out of range: %ld<1\n", RNG);
		return -ERANGE;
	}
	if (DAT < 1) {
		dev_err(dev->dev, "DAT is out of range: %ld<1\n", DAT);
		return -ERANGE;
	}
	/* Escreve as informacoes da frequencia e duty cycle */
	__raw_writel(RNG, PWM_RNG1);
	udelay(10);
	__raw_writel(DAT, PWM_DAT1);
	udelay(10);
	/* Habilita modo MSEN, inicializando PWM */
	__raw_writel(0x81, PWM_CTL);
	udelay(10);
	dev->active = 1;
	printk(KERN_INFO "PWM: pwm_activate done");
	return 0;
}

static int pwm_deactivate(struct pwm_device *dev) {
	printk(KERN_INFO "PWM: pwm_deactivate...");
	/* Desativa o PWM */
	__raw_writel(0,PWM_CTL);
	udelay(10);
	SET_GPIO_ALT(18,0);
	udelay(10);
	dev->active = 0;
	printk(KERN_INFO "PWM: pwm_deactivate done");
	return 0;
}
static ssize_t duty_get(struct device *d,
		struct device_attribute *attr, char *buf)
{
	ssize_t ret;
	struct pwm_device *dev = dev_get_drvdata(d);
	mutex_lock(&sysfs_lock);
	ret = sprintf(buf, "%d%%\n", dev->duty);
	mutex_unlock(&sysfs_lock);
	return ret;
}

static ssize_t duty_set(struct device *d,
						struct device_attribute *attr, 
						const char *buf, 
						size_t count)
{
	ssize_t ret = 0;
	long new_duty;
	struct pwm_device *dev = dev_get_drvdata(d);
	mutex_lock(&sysfs_lock);
	ret = kstrtol(buf,0,&new_duty);
	if (ret == 0) {
		if (new_duty > 0 && new_duty < 100) {
			dev->duty = new_duty;
			if (dev->immediate) {
				pwm_activate(dev);
			}
		} else {
			ret = -ERANGE;
		}
	}
	mutex_unlock(&sysfs_lock);
	return ret?ret:count;
}

static DEVICE_ATTR(duty,(S_IWUSR | S_IRUGO),duty_get,duty_set);

static ssize_t freq_get(struct device *d,
						struct device_attribute *attr, 
						char *buf)
{
	ssize_t ret;
	struct pwm_device *dev = dev_get_drvdata(d);
	mutex_lock(&sysfs_lock);
	ret = sprintf(buf,"%d\n",dev->frequency);
	mutex_unlock(&sysfs_lock);
	return ret;
}

static ssize_t freq_set(struct device *d,
						struct device_attribute *attr,
						const char *buf,
						size_t count)
{
	ssize_t ret = 0;
	long new_freq;
	struct pwm_device *dev = dev_get_drvdata(d);
	mutex_lock(&sysfs_lock);
	ret = kstrtol(buf, 0, &new_freq);
	if (ret == 0) {
		dev->frequency 	= new_freq;
		if (dev->immediate) {
			pwm_activate(dev);
		}
	}
	mutex_unlock(&sysfs_lock);
	return ((ret)?ret:count);
}

static DEVICE_ATTR(frequency,(S_IWUSR | S_IRUGO),freq_get,freq_set);

static struct attribute *pwm_sysfs_entries[] = {
	&dev_attr_duty.attr,
	&dev_attr_frequency.attr,
	NULL
};

static struct attribute_group pwm_attribute_group = {
	.name 	= NULL,
	.attrs 	= pwm_sysfs_entries,
};

static struct class pwm_class = {
	.name 	= CLASS_NAME,
	.owner 	= THIS_MODULE,
};

int __init pwm_init(void)
{
	printk(KERN_INFO "PWM: staring...");
	ssize_t ret = 0;
	/* Registra a classe para o device PWM */
	ret = class_register(&pwm_class);
	if (ret < 0) {
		pr_err("Unable to register class");
		return -EINVAL;
	}
	/* Cria o device PWM e inicializa algumas configuracoes */
	pwm.immediate = 1;
	pwm.duty = 50;
	pwm.mcf = 16000;
	pwm.frequency = 0;			
	pwm.dev = device_create(&pwm_class,&platform_bus,MKDEV(0,0),&pwm,"pwm_module");
	if (IS_ERR(pwm.dev)) {
		pr_err("device_create failed\n");
		return -EINVAL;
	}
	/* Cria o sysfs para o device PWM */
	ret = sysfs_create_group(&pwm.dev->kobj,&pwm_attribute_group);
	/* Inicializa os registradores */
	clk_reg  = ioremap(CLOCK_BASE, 1024);
	pwm_reg  = ioremap(PWM_BASE,   1024);
	gpio_reg = ioremap(GPIO_BASE,  1024);
	/* Ativa o PWM */
	pwm_activate(&pwm);
	printk(KERN_INFO "PWM: staring done.");
	return 0;
}

void __exit pwm_cleanup(void)
{
	printk(KERN_INFO "PWM: stopping...");
	/* Libera o que foi usado */
	if (pwm.loaded) {	
		pwm_deactivate(&pwm);
	}
	sysfs_remove_group(&pwm.dev->kobj,&pwm_attribute_group);
	if (pwm.dev) {
		device_unregister(pwm.dev);
	}
	iounmap(gpio_reg);
	iounmap(pwm_reg);
	iounmap(clk_reg);
	class_unregister(&pwm_class);
	printk(KERN_INFO "PWM: stopping done.");
}

/* definicoes basicas para o modulo */
module_init(pwm_init);
module_exit(pwm_cleanup);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Victor Wilvert Antunes");
MODULE_ALIAS("platform:BCM2837_pwm");


