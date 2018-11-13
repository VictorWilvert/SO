
#include "pwm_music.h"

PWMMusic::PWMMusic() {
	m_duty = open("/sys/class/rpi-pwm/pwm_dev/duty",O_WRONLY|O_APPEND);
	write(m_duty,"50",2);
	m_freq = open("/sys/class/rpi-pwm/pwm_dev/frequency",O_WRONLY|O_APPEND);
	write(m_freq,"0",1);
}

PWMMusic::~PWMMusic() {
	close(m_duty);
	close(m_freq);
}

void PWMMusic::playTone(Tone t_tone) {
	writeFreq(t_tone.note);
	int duration = 1000/float(t_tone.duration);
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
	writeFreq(0);
}

void PWMMusic::playMusic(std::vector<Tone> t_music) {
	for (const auto& tone : t_music) {
		playTone(tone);
	}
}

void PWMMusic::writeFreq(unsigned int freq) {
	std::string data = std::to_string(freq);
	write(m_freq,data.c_str(),data.size());
}

void PWMMusic::writeDuty(unsigned int duty) {
	std::string data = std::to_string(duty);
	write(m_freq,data.c_str(),data.size());
}