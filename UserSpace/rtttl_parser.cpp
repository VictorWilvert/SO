
#include "rtttl_parser.h"
#include <iostream>

RTTTLParser::RTTTLParser() 
	: m_name{""}, m_duration{-1}, m_octave{-1}, m_tempo{-1}
{}

RTTTLParser::RTTTLParser(std::string t_arq) {
	parse(t_arq);
}

void RTTTLParser::parse(std::string t_arq) {
	std::ifstream fd(t_arq);
	std::cout << "parse: " << t_arq << std::endl;
	if (fd.fail()) {
		m_name = "";
		m_duration = -1;
		m_octave = -1;
		m_tempo = -1;
		m_notes.clear();
	}
	std::cout << "valid" <<std::endl;
	/* le todo o arquivo para uma std::string */
	std::string data((std::istreambuf_iterator<char>(fd)),
			(std::istreambuf_iterator<char>()));
	/* separando o texto atraves do uso de tokens */
    	std::istringstream is(data);
    	std::getline(is,m_name,':');	
    	std::string str;
    	std::getline(is,str,',');
    	str.erase(0,2);
    	m_duration = strToInt(str);
    	std::getline(is,str,',');
    	str.erase(0,2);
    	m_octave = strToInt(str);
    	std::getline(is,str,':');
    	str.erase(0,2);
    	m_tempo = strToInt(str);
    	/* leitura das notas e duracaoes */
    	while (std::getline(is,str,',')) {
    		Tone tone;
    		bool dot = false;
   		/* durancao da nota */
   		if (str[0] < 48 || str[0] > 57) {
   			tone.duration = m_duration;
   		} else if (str[0] == '1' || str[1] == '6') {
   			tone.duration = 16;
   			str.erase(0,2);
   		} else if (str[0] == '3') {
   			tone.duration = 32;
   			str.erase(0,2);
   		} else {
   			tone.duration = (int)str[0] - 48;
   			str.erase(0,1);
   		}
   		if (str[0] == '.') {
   			dot = true;
   			str.erase(0,1);
   		}
   		/* nota em si */
   		if (str[0] == 'p' || str[0] == 'P') {
   			tone.note = 0;
   		} else if (str[0] == 'a' || str[0] == 'A') {
			if (str[1] == '#') {
   				str.erase(1,1);
   				if (str.size() == 1) {
   					switch (m_octave) {
		   				case 4:
		   					tone.note = AS4;
		   					break;
		   				case 5:
		   					tone.note = AS5;
		   					break;
		   				case 6:
		   					tone.note = AS6;
		   					break;
		   				case 7:
		   					tone.note = AS7;
		   					break;
		   			}
	   			} else  { 
	   				if (str[1] == '.') {
		   				dot = true;
		   				str.erase(1,1);	
		   			}
		   			if (str.size() == 1) {
			   			switch (m_octave) {
			   				case 4:
			   					tone.note = AS4;
			   					break;
			   				case 5:
			   					tone.note = AS5;
			   					break;
			   				case 6:
			   					tone.note = AS6;
			   					break;
			   				case 7:
			   					tone.note = AS7;
			   					break;
			   			}
		   			} else {
			   			switch (((int)str[1]-48)) {
			   				case 4:
			   					tone.note = AS4;
			   					break;
			   				case 5:
			   					tone.note = AS5;
			   					break;
			   				case 6:
			   					tone.note = AS6;
			   					break;
			   				case 7:
			   					tone.note = AS7;
			   					break;
			   			}
		   			}
		   		}
   			} else {
	   			if (str[1] == '.') {
		   			dot = true;
		   			str.erase(1,1);	
		   		}
		   		if (str.size() == 1) {
			   		switch (m_octave) {
			   			case 4:
			   				tone.note = A4;
			   				break;
			   			case 5:
			   				tone.note = A5;
			   				break;
			   			case 6:
			   				tone.note = A6;
			   				break;
			   			case 7:
			   				tone.note = A7;
			   				break;
			   		}
		   		} else {
			   		switch (((int)str[1]-48)) {
			   			case 4:
			   				tone.note = A4;
			   				break;
			   			case 5:
			   				tone.note = A5;
			   				break;
			   			case 6:
			   				tone.note = A6;
			   				break;
			   			case 7:
			   				tone.note = A7;
			   				break;
			   		}
		   		}
		   	}   
   		} else if (str[0] == 'b' || str[0] == 'B') {
			if (str[1] == '.') {
				dot = true;
				str.erase(1,1);	
			}
			if (str.size() == 1) {
	   			switch (m_octave) {
	   				case 4:
	   					tone.note = B4;
	   					break;
	   				case 5:
	   					tone.note = B5;
	   					break;
	   				case 6:
	   					tone.note = B6;
	   					break;
	   				case 7:
	   					tone.note = B7;
	   					break;
	   			}
			} else {
	   			switch (((int)str[1]-48)) {
	   				case 4:
	   					tone.note = B4;
	   					break;
	   				case 5:
	   					tone.note = B5;
	   					break;
	   				case 6:
	   					tone.note = B6;
	   					break;
	   				case 7:
	   					tone.note = B7;
	   					break;
	   			}
			}
   		} else if (str[0] == 'c' || str[0] == 'C') {
			if (str[1] == '#') {
   				str.erase(1,1);
   				if (str.size() == 1) {
   					switch (m_octave) {
		   				case 4:
		   					tone.note = CS4;
		   					break;
		   				case 5:
		   					tone.note = CS5;
		   					break;
		   				case 6:
		   					tone.note = CS6;
		   					break;
		   				case 7:
		   					tone.note = CS7;
		   					break;
		   			}
	   			} else  { 
	   				if (str[1] == '.') {
		   				dot = true;
		   				str.erase(1,1);	
		   			}
		   			if (str.size() == 1) {
			   			switch (m_octave) {
			   				case 4:
			   					tone.note = CS4;
			   					break;
			   				case 5:
			   					tone.note = CS5;
			   					break;
			   				case 6:
			   					tone.note = CS6;
			   					break;
			   				case 7:
			   					tone.note = CS7;
			   					break;
			   			}
		   			} else {
			   			switch (((int)str[1]-48)) {
			   				case 4:
			   					tone.note = CS4;
			   					break;
			   				case 5:
			   					tone.note = CS5;
			   					break;
			   				case 6:
			   					tone.note = CS6;
			   					break;
			   				case 7:
			   					tone.note = CS7;
			   					break;
			   			}
		   			}
		   		}
   			} else {
	   			if (str[1] == '.') {
		   			dot = true;
		   			str.erase(1,1);	
		   		}
		   		if (str.size() == 1) {
			   		switch (m_octave) {
			   			case 4:
			   				tone.note = C4;
			   				break;
			   			case 5:
			   				tone.note = C5;
			   				break;
			   			case 6:
			   				tone.note = C6;
			   				break;
			   			case 7:
			   				tone.note = C7;
			   				break;
			   		}
		   		} else {
			   		switch (((int)str[1]-48)) {
			   			case 4:
			   				tone.note = C4;
			   				break;
			   			case 5:
			   				tone.note = C5;
			   				break;
			   			case 6:
			   				tone.note = C6;
			   				break;
			   			case 7:
			   				tone.note = C7;
			   				break;
			   		}
		   		}
		   	}   
   		} else if (str[0] == 'd' || str[0] == 'D') {
			if (str[1] == '#') {
   				str.erase(1,1);
   				if (str.size() == 1) {
   					switch (m_octave) {
		   				case 4:
		   					tone.note = DS4;
		   					break;
		   				case 5:
		   					tone.note = DS5;
		   					break;
		   				case 6:
		   					tone.note = DS6;
		   					break;
		   				case 7:
		   					tone.note = DS7;
		   					break;
		   			}
	   			} else  { 
	   				if (str[1] == '.') {
		   				dot = true;
		   				str.erase(1,1);	
		   			}
		   			if (str.size() == 1) {
			   			switch (m_octave) {
			   				case 4:
			   					tone.note = DS4;
			   					break;
			   				case 5:
			   					tone.note = DS5;
			   					break;
			   				case 6:
			   					tone.note = DS6;
			   					break;
			   				case 7:
			   					tone.note = DS7;
			   					break;
			   			}
		   			} else {
			   			switch (((int)str[1]-48)) {
			   				case 4:
			   					tone.note = DS4;
			   					break;
			   				case 5:
			   					tone.note = DS5;
			   					break;
			   				case 6:
			   					tone.note = DS6;
			   					break;
			   				case 7:
			   					tone.note = DS7;
			   					break;
			   			}
		   			}
		   		}
   			} else {
	   			if (str[1] == '.') {
		   			dot = true;
		   			str.erase(1,1);	
		   		}
		   		if (str.size() == 1) {
			   		switch (m_octave) {
			   			case 4:
			   				tone.note = D4;
			   				break;
			   			case 5:
			   				tone.note = D5;
			   				break;
			   			case 6:
			   				tone.note = D6;
			   				break;
			   			case 7:
			   				tone.note = D7;
			   				break;
			   		}
		   		} else {
			   		switch (((int)str[1]-48)) {
			   			case 4:
			   				tone.note = D4;
			   				break;
			   			case 5:
			   				tone.note = D5;
			   				break;
			   			case 6:
			   				tone.note = D6;
			   				break;
			   			case 7:
			   				tone.note = D7;
			   				break;
			   		}
		   		}
		   	}   
   		} else if (str[0] == 'e' || str[0] == 'E') {
			if (str[1] == '.') {
				dot = true;
				str.erase(1,1);	
			}
			if (str.size() == 1) {
	   			switch (m_octave) {
	   				case 4:
	   					tone.note = E4;
	   					break;
	   				case 5:
	   					tone.note = E5;
	   					break;
	   				case 6:
	   					tone.note = E6;
	   					break;
	   				case 7:
	   					tone.note = E7;
	   					break;
	   			}
			} else {
	   			switch (((int)str[1]-48)) {
	   				case 4:
	   					tone.note = E4;
	   					break;
	   				case 5:
	   					tone.note = E5;
	   					break;
	   				case 6:
	   					tone.note = E6;
	   					break;
	   				case 7:
	   					tone.note = E7;
	   					break;
	   			}
			}
 		} else if (str[0] == 'f' || str[0] == 'F') {
			if (str[1] == '#') {
   				str.erase(1,1);
   				if (str.size() == 1) {
   					switch (m_octave) {
		   				case 4:
		   					tone.note = FS4;
		   					break;
		   				case 5:
		   					tone.note = FS5;
		   					break;
		   				case 6:
		   					tone.note = FS6;
		   					break;
		   				case 7:
		   					tone.note = FS7;
		   					break;
		   			}
	   			} else  { 
	   				if (str[1] == '.') {
		   				dot = true;
		   				str.erase(1,1);	
		   			}
		   			if (str.size() == 1) {
			   			switch (m_octave) {
			   				case 4:
			   					tone.note = FS4;
			   					break;
			   				case 5:
			   					tone.note = FS5;
			   					break;
			   				case 6:
			   					tone.note = FS6;
			   					break;
			   				case 7:
			   					tone.note = FS7;
			   					break;
			   			}
		   			} else {
			   			switch (((int)str[1]-48)) {
			   				case 4:
			   					tone.note = FS4;
			   					break;
			   				case 5:
			   					tone.note = FS5;
			   					break;
			   				case 6:
			   					tone.note = FS6;
			   					break;
			   				case 7:
			   					tone.note = FS7;
			   					break;
			   			}
		   			}
		   		}
   			} else {
	   			if (str[1] == '.') {
		   			dot = true;
		   			str.erase(1,1);	
		   		}
		   		if (str.size() == 1) {
			   		switch (m_octave) {
			   			case 4:
			   				tone.note = F4;
			   				break;
			   			case 5:
			   				tone.note = F5;
			   				break;
			   			case 6:
			   				tone.note = F6;
			   				break;
			   			case 7:
			   				tone.note = F7;
			   				break;
			   		}
		   		} else {
			   		switch (((int)str[1]-48)) {
			   			case 4:
			   				tone.note = F4;
			   				break;
			   			case 5:
			   				tone.note = F5;
			   				break;
			   			case 6:
			   				tone.note = F6;
			   				break;
			   			case 7:
			   				tone.note = F7;
			   				break;
			   		}
		   		}
		   	}   		
   		} else if (str[0] == 'g' || str[0] == 'G') {
			if (str[1] == '#') {
   				str.erase(1,1);
   				if (str.size() == 1) {
   					switch (m_octave) {
		   				case 4:
		   					tone.note = GS4;
		   					break;
		   				case 5:
		   					tone.note = GS5;
		   					break;
		   				case 6:
		   					tone.note = GS6;
		   					break;
		   				case 7:
		   					tone.note = GS7;
		   					break;
		   			}
	   			} else  { 
	   				if (str[1] == '.') {
		   				dot = true;
		   				str.erase(1,1);	
		   			}
		   			if (str.size() == 1) {
			   			switch (m_octave) {
			   				case 4:
			   					tone.note = GS4;
			   					break;
			   				case 5:
			   					tone.note = GS5;
			   					break;
			   				case 6:
			   					tone.note = GS6;
			   					break;
			   				case 7:
			   					tone.note = GS7;
			   					break;
			   			}
		   			} else {
			   			switch (((int)str[1]-48)) {
			   				case 4:
			   					tone.note = GS4;
			   					break;
			   				case 5:
			   					tone.note = GS5;
			   					break;
			   				case 6:
			   					tone.note = GS6;
			   					break;
			   				case 7:
			   					tone.note = GS7;
			   					break;
			   			}
		   			}
		   		}
   			} else {
	   			if (str[1] == '.') {
		   			dot = true;
		   			str.erase(1,1);	
		   		}
		   		if (str.size() == 1) {
			   		switch (m_octave) {
			   			case 4:
			   				tone.note = G4;
			   				break;
			   			case 5:
			   				tone.note = G5;
			   				break;
			   			case 6:
			   				tone.note = G6;
			   				break;
			   			case 7:
			   				tone.note = G7;
			   				break;
			   		}
		   		} else {
			   		switch (((int)str[1]-48)) {
			   			case 4:
			   				tone.note = G4;
			   				break;
			   			case 5:
			   				tone.note = G5;
			   				break;
			   			case 6:
			   				tone.note = G6;
			   				break;
			   			case 7:
			   				tone.note = G7;
			   				break;
			   		}
		   		}
		   	}  
   		}
   		if (str[str.size()-1] == '.') {
   			dot = true;	
   		}
   		m_notes.push_back(tone);
   		/* caso haja um ponto adicionar meia nota */
   		if (dot) {
   			tone.duration *= 2;
   			m_notes.push_back(tone);
   		}
    	}
}

int RTTTLParser::strToInt(std::string t_str) {
	std::stringstream ss(t_str);
	int ret;
	ss >> ret;
	return ret;
}
