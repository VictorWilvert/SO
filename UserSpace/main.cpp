
#include "pwm_music.h"
#include "notes.h"
#include <iostream>
#include "rtttl_parser.h"

int main(void) {
	RTTTLParser p("rtttl.txt");
	PWMMusic pwm;
	while (1) {
		pwm.playMusic(p.notes());
	}
	return 0;
}