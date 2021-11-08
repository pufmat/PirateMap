#include "NBTByte.h"

NBTByte::NBTByte(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	data = br.read();
}

NBTByte::~NBTByte(){

}

