
#include "buzzer_player.h"

BuzzerPlayer::BuzzerPlayer() {
	/* abre os arquivos usadas para alterar a frequencia e duty cycle */
	m_duty = open("/sys/class/pwm_device/pwm_module/duty",O_WRONLY|O_APPEND);
	write(m_duty,"50",2);
	m_freq = open("/sys/class/pwm_device/pwm_module/frequency",O_WRONLY|O_APPEND);
	write(m_freq,"0",1);
}

BuzzerPlayer::~BuzzerPlayer() {
	/* fecha os arquivos usadas para alterar a frequencia e duty cycle */
	close(m_duty);
	close(m_freq);
}

void BuzzerPlayer::playTone(Tone t_tone) {
	/* Calculo da duracao da uma nota */
	int duration = 1000 / float(t_tone.duration);
	int delay = ((60 / m_tempo) - duration) / 2;
	/* Toca a nota */
	//writeFreq(0);
	//std::this_thread::sleep_for(std::chrono::milliseconds(delay / 2));
	writeFreq(t_tone.note);
	std::this_thread::sleep_for(std::chrono::milliseconds(duration));
	writeFreq(0);
	//std::this_thread::sleep_for(std::chrono::milliseconds(delay / 2));
}

void BuzzerPlayer::playMusic(std::vector<Tone> t_music) {
	/* toca toda a musica passada */
	for (const auto& tone : t_music) {
		playTone(tone);
	}
}

void BuzzerPlayer::writeFreq(unsigned int freq) {
	std::string data = std::to_string(freq);
	write(m_freq,data.c_str(),data.size());
}

void BuzzerPlayer::writeDuty(unsigned int duty) {
	std::string data = std::to_string(duty);
	write(m_freq,data.c_str(),data.size());
}
