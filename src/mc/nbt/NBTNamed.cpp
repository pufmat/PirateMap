#include "NBTNamed.h"

NBTNamed::NBTNamed(BufferedReader& br, bool noName){
	if(!noName){
		uint_least16_t size = static_cast<uint_least16_t>(static_cast<uint_least16_t>(br.read()) << 8);
		size = static_cast<uint_least16_t>(size | static_cast<uint_least16_t>(br.read()));

		for(uint_least16_t i = 0; i < size; i++){
			name += static_cast<char>(br.read());
		}
	}
}

NBTNamed::NBTNamed(){

}

NBTNamed::~NBTNamed(){

}

