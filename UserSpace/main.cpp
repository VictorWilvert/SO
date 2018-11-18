
#include "rtttl_parser.h"
#include "buzzer_player.h"
#include "notes.h"
#include <iostream>

int main(void) {
	RTTTLParser parser;
	BuzzerPlayer buzzer;
	std::string music;
	unsigned int count;
	std::cout << "Tocador de musicas no formato RTTTL" << std::endl
	std::cout << "As musicas de exemplo se encontram no diretorio 'examples'" << std::endl;
	std::cout << std::endl;
	while (1) {
		
		std::cout << "Qual musica se deseja ouvir: ";
		std::cin >> music;
		parser(music);
		std::cout << "Quantas vezes: ";
		std::cin >> count;
		buzzer.tempo(parser.tempo());
		for(auto i = 0;i < count;++i) {
			buzzer.playMusic(parser.notes());
		}
	}
	return 0;
}
