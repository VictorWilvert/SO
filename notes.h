
#ifndef NOTES_H
#define NOTES_H

/*
 * 	@brief	struct que representa um tom, composto por uma nota e uma duracao.
 */
struct Tone {
	int note;		/**< nota do tom */
	int duration; 	/**< duracao do tom */
	
};	/* struct Tone */

/* Notas no padrao ANSI com suas respctivas frequncias(S = #) */
const int B0  	=	31;
const int C1  	=	33;
const int CS1 	=	35;
const int D1  	=	37;
const int DS1 	=	39;
const int E1  	=	41;
const int F1  	=	44;
const int FS1 	=	46;
const int G1  	=	49;
const int GS1 	=	52;
const int A1  	=	55;
const int AS1 	=	58;
const int B1  	=	62;
const int C2  	=	65;
const int CS2 	=	69;
const int D2  	=	73;
const int DS2 	=	78;
const int E2  	=	82;
const int F2  	=	87;
const int FS2 	=	93;
const int G2  	=	98;
const int GS2 	=  104;
const int A2  	=  110;
const int AS2 	=  117;
const int B2  	=  123;
const int C3  	=  131;
const int CS3 	=  139;
const int D3  	=  147;
const int DS3 	=  156;
const int E3  	=  165;
const int F3  	=  175;
const int FS3 	=  185;
const int G3  	=  196;
const int GS3 	=  208;
const int A3  	=  220;
const int AS3 	=  233;
const int B3  	=  247;
const int C4  	=  262;
const int CS4 	=  277;
const int D4  	=  294;
const int DS4 	=  311;
const int E4  	=  330;
const int F4  	=  349;
const int FS4 	=  370;
const int G4  	=  392;
const int GS4 	=  415;
const int A4  	=  440;
const int AS4 	=  466;
const int B4  	=  494;
const int C5  	=  523;
const int CS5 	=  554;
const int D5  	=  587;
const int DS5 	=  622;
const int E5  	=  659;
const int F5  	=  698;
const int FS5 	=  740;
const int G5  	=  784;
const int GS5 	=  831;
const int A5  	=  880;
const int AS5 	=  932;
const int B5  	=  988;
const int C6  	= 1047;
const int CS6 	= 1109;
const int D6  	= 1175;
const int DS6 	= 1245;
const int E6  	= 1319;
const int F6  	= 1397;
const int FS6 	= 1480;
const int G6  	= 1568;
const int GS6 	= 1661;
const int A6  	= 1760;
const int AS6 	= 1865;
const int B6  	= 1976;
const int C7  	= 2093;
const int CS7 	= 2217;
const int D7  	= 2349;
const int DS7 	= 2489;
const int E7  	= 2637;
const int F7  	= 2794;
const int FS7 	= 2960;
const int G7  	= 3136;
const int GS7 	= 3322;
const int A7  	= 3520;
const int AS7 	= 3729;
const int B7  	= 3951;
const int C8  	= 4186;
const int CS8 	= 4435;
const int D8  	= 4699;
const int DS8 	= 4978;

#endif	/* NOTES_H */