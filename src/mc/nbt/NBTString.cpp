#include "NBTString.h"

NBTString::NBTString(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	uint_least16_t size = static_cast<uint_least16_t>(static_cast<uint_least16_t>(br.read()) << 8);
	size = static_cast<uint_least16_t>(size | static_cast<uint_least16_t>(br.read()));

	for(uint_least16_t i = 0; i < size; i++){
		data += static_cast<char>(br.read());
	}
}

NBTString::~NBTString(){

}

