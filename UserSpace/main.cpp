
#include "rtttl_parser.h"
#include "buzzer_player.h"
#include "notes.h"
#include <iostream>

int main(void) {
	RTTTLParser parser("rtttl_examples/AC\ DC\ -\ Highway\ to\ Hell.txt");
	BuzzerPlayer buzzer;
	buzzer.tempo(parser.tempo());
	while (1) {
		buzzer.playMusic(parser.notes());
	}
	return 0;
}
