
#include "rtttl_parser.h"
#include "buzzer_player.h"
#include "notes.h"
#include <iostream>

int main(void) {
	RTTTLParser parser;
	BuzzerPlayer buzzer;
	std::string music;
	unsigned int count;
	std::cout << "Tocador de musicas no formato RTTTL" << std::endl;
	std::cout << "As musicas de exemplo se encontram no diretorio 'examples'" << std::endl;
	std::cout << std::endl;
	while (1) {
		std::cout << "Qual musica se deseja ouvir: ";
		std::cin >> music;
		parser.parse("examples/halloween.txt");
		std::cout << "Quantas vezes: ";
		std::cin >> count;
		buzzer.tempo(parser.tempo());
		std::cout << "vt size(): " << parser.notes().size() << std::endl;
		std::cout << count << std::endl;
		for(unsigned int i = 0;i < count;++i) {
			buzzer.playMusic(parser.notes());
		}
	}
	return 0;
}
