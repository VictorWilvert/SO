
#ifndef BUZZER_PLAYER_H
#define BUZZER_PLAYER_H

#include <thread>       /* Para uso de sleep_for() */
#include <vector>       
#include <sys/types.h>  /* Bibliotecas para as chamadas de sistema */
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "notes.h"      /* Notacao das notas e do tom */

/**
 *	@brief Classe responsavel pela leitura da musica e interpretacao dela
 *			   para passagem para o modulo PWM, com o intuito de gerar o som no
 *			   buzzer.
 */
class BuzzerPlayer {
  public:
    /**
     *  @brief	Construtor do BuzzerPlayer que cuida de inicializar o modulo PWM.
     */
    BuzzerPlayer();
    
    /**
     *  @brief	Destrutor do BuzzerPlayer que cuida de finalizar o modulo PWM.
     */
    ~BuzzerPlayer();

    /**
     *  @brief	Toca um Tone no buzzer.
     *  @param	t_tone	O tom a ser tocado.
     */
    void playTone(Tone t_tone);

    /**
     *  @brief  Altera o tempo/bpm do tocador.
     *  @param  t_tempo O novo tempo/bpm.
     */
    void tempo(unsigned int t_tempo) { m_tempo = t_tempo; }

    /**
     *  @brief  Retorna o tempo/bpm usado.
     */
    unsigned int tempo() const { return m_tempo; }
    
    /**
     *  @brief	Toca uma musica, ou seja um vetor de tom.
     *  @param	t_music	A musica a ser tocada.
     */
    void playMusic(std::vector<Tone> t_music);

  private:
    /**
     *  @brief  Altera a frequencia do modulo PWM.
     *  @param  t_freq  Novo valor de frequencia.
     */
    void writeFreq(unsigned int t_freq);

    /**
     *  @brief  Altera o duty cycle do modulo PWM.
     *  @param  t_duty  Novo valor de duty cycle.
     */
    void writeDuty(unsigned int t_duty);

    unsigned int m_tempo;     /**< Tempo/bpm do tocador */
    int m_duty;               /**< Duty cycle do PWM    */ 
    int m_freq;               /**< Frequencia do PWM    */

};  /* class BuzzerPlayer */

#endif  /* BUZZER_PLAYER_H */
