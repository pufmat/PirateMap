#include "NBTList.h"

NBTList::NBTList(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	byte type = br.read();

	uint_least32_t size = (static_cast<uint_least32_t>(br.read()) << 24);
	size |= (static_cast<uint_least32_t>(br.read()) << 16);
	size |= (static_cast<uint_least32_t>(br.read()) << 8);
	size |= static_cast<uint_least32_t>(br.read());

	for(uint_least32_t i = 0; i < size; i++){
		data.push_back(NBTTag::create(br, type, true));
	}
}

NBTList::~NBTList(){

}

