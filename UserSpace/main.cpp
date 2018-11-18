
#include "rtttl_parser.h"
#include "buzzer_player.h"
#include "notes.h"
#include <iostream>

int main(void) {
	RTTTLParser parser("rtttl_examples/Ac Dc - Back In Black.txt");
	BuzzerPlayer buzzer;
	buzzer.tempo(parser.tempo());
	while (1) {
		buzzer.playMusic(parser.notes());
	}
	return 0;
}
