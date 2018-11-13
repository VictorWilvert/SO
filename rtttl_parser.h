
#ifndef RTTTL_PARSER_H
#define RTTTL_PARSER_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

#include "notes.h"

/**
 *	@brief	Analisador de arquivos do formato Ring Tone Text Transfer 
 *			Language(RTTTL), os quais eram usados para os toques de celular de
 *			celulares Nokia. 
 */
class RTTTLParser {
  public:
  	/**
  	 *
  	 */
  	RTTTLParser();

  	/**
  	 *
  	 */
  	RTTTLParser(std::string t_arq);

  	/**
  	 *
  	 */
  	void parse(std::string t_arq);

  	/**
  	 *
  	 */
  	std::string name() const { return m_name; }

  	/**
  	 *	
  	 */
  	int duration() const { return m_duration; }

  	/**
  	 *
  	 */
  	int octave() const { return m_octave; }

  	/**
  	 *
  	 */
  	int tempo() const { return m_tempo; }

  	/**
  	 *
  	 */
  	std::vector<Tone> notes() const { return m_notes; }

  private:
  	/**
	 *
  	 */
  	int strToInt(std::string t_str);

  	std::string m_name;				/**< o nome da musica   */
  	int m_duration;					/**< a duracao padrao   */
  	int m_octave;					/**< a oitava padrao    */
  	int m_tempo;					/**< batidas por minuto */
  	std::vector<Tone> m_notes;		/**< as notas da musica */

};

#endif