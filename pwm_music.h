
#ifndef PWM_MUSIC_H
#define PWM_MUSIC_H

#include <thread> 
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "notes.h"

/* 
 *	@brief 	classe responsavel pela leitura da musica e e interpretacao dela
 *			para passagem para o modulo PWM, com o intuito de gerar o som no
 *			buzzer.
 */
class PWMMusic {
  public:
  	/*
  	 *	@brief	Construtor do PWMMusic que cuida de inicializar o modulo PWM.
  	 */
  	PWMMusic();

  	/*
  	 *	@brief	destrutor do PWMMusic que cuida de finalizar o modulo PWM.
  	 */
  	~PWMMusic();

  	/*
  	 *	@brief	Toca um Tone no buzzer.		
  	 *	@param	t_tone	O tom a ser tocado.
  	 */
  	void playTone(Tone t_tone);

  	/*
  	 *	@brief	Toca uma musica, ou seja um vetor de tom.
  	 *	@param	t_music	A musica a ser tocada.
  	 */
    void playMusic(std::vector<Tone> t_music);

  private:
    void writeFreq(unsigned int freq);

    void writeDuty(unsigned int duty);

    int m_duty;
    int m_freq;
};

#endif