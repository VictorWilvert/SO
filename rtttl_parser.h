
#ifndef RTTTL_PARSER_H
#define RTTTL_PARSER_H

#include <vector>
#include <sstream>        /* Usados para manipular strings */
#include <fstream>        
#include <string>
#include "notes.h"        /* Notacao das notas e do tom */

/**
 *	@brief  Analisador de arquivos do formato Ring Tone Text Transfer 
 *			    Language(RTTTL), os quais eram usados para os toques de celular de
 *			    celulares Nokia. 
 */
class RTTTLParser {
  public:

  	/**
  	 *  @brief  Construtor padrao que inicializa tudo com valores invalidos.   
  	 */
  	RTTTLParser();

  	/**
  	 *  @brief  Construtor que ja realiza a analise do arquivo passado e 
     *          armazena suas informacaoes.
     *  @param  t_arq String que contem o arquivo.   
  	 */
  	RTTTLParser(std::string t_arq);

  	/**
  	 *  @brief  Realiza a analise do arquivo passado e armazena suas 
     *          informacoes.
     *  @param  t_arq String que contem o arquivo.
  	 */
  	void parse(std::string t_arq);

  	/**
  	 *  @brief  Retorna o nome da musica.
  	 */
  	std::string name() const { return m_name; }

  	/**
  	 *	@brief  Retorna a duracao padrao.
  	 */
  	int duration() const { return m_duration; }

  	/**
  	 *  @brief  Retorna oitava padrao.
  	 */
  	int octave() const { return m_octave; }

  	/**
  	 *  @brief  Retorna o tempo/bpm.
  	 */
  	int tempo() const { return m_tempo; }

  	/**
  	 *  @brief  Retorna a musica, representada por um vetor de tons.
  	 */
  	std::vector<Tone> notes() const { return m_notes; }

  private:
  	/**
	   *  @brief  Converte uma string para um inteiro.
     *  @param  t_str A string a ser convertida. 
  	 */
  	int strToInt(std::string t_str);

  	std::string m_name;				    /**< O nome da musica   */
  	int m_duration;					      /**< A duracao padrao   */
  	int m_octave;					        /**< A oitava padrao    */
  	int m_tempo;					        /**< Batidas por minuto */
  	std::vector<Tone> m_notes;	  /**< As notas da musica */

};  /* class RTTTLParser */

#endif  /* RTTTL_PARSER_H */