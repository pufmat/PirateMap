#include "NBTInt.h"

NBTInt::NBTInt(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	data = (static_cast<uint_least32_t>(br.read()) << 24);
	data |= (static_cast<uint_least32_t>(br.read()) << 16);
	data |= (static_cast<uint_least32_t>(br.read()) << 8);
	data |= static_cast<uint_least32_t>(br.read());
}

NBTInt::~NBTInt(){

}

