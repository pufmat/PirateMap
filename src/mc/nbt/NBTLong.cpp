#include "NBTLong.h"

NBTLong::NBTLong(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	data = (static_cast<uint_least64_t>(br.read()) << 56);
	data |= (static_cast<uint_least64_t>(br.read()) << 48);
	data |= (static_cast<uint_least64_t>(br.read()) << 40);
	data |= (static_cast<uint_least64_t>(br.read()) << 32);
	data |= (static_cast<uint_least64_t>(br.read()) << 24);
	data |= (static_cast<uint_least64_t>(br.read()) << 16);
	data |= (static_cast<uint_least64_t>(br.read()) << 8);
	data |= static_cast<uint_least64_t>(br.read());
}

NBTLong::~NBTLong(){

}

