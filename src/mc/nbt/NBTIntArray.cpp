#include "NBTIntArray.h"

NBTIntArray::NBTIntArray(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	uint_least32_t size = (static_cast<uint_least32_t>(br.read()) << 24);
	size |= (static_cast<uint_least32_t>(br.read()) << 16);
	size |= (static_cast<uint_least32_t>(br.read()) << 8);
	size |= static_cast<uint_least32_t>(br.read());

	for(uint_least32_t i = 0; i < size; i++){
		uint_least32_t value = (static_cast<uint_least32_t>(br.read()) << 24);
		value |= (static_cast<uint_least32_t>(br.read()) << 16);
		value |= (static_cast<uint_least32_t>(br.read()) << 8);
		value |= static_cast<uint_least32_t>(br.read());
		data.push_back(value);
	}
}

NBTIntArray::~NBTIntArray(){

}

