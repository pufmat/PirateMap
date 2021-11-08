#include "NBTShort.h"

NBTShort::NBTShort(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	data = static_cast<uint_least16_t>(static_cast<uint_least16_t>(br.read()) << 8);
	data = static_cast<uint_least16_t>(data | static_cast<uint_least16_t>(br.read()));
}

NBTShort::~NBTShort(){

}

