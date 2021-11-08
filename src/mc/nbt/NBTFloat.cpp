#include "NBTFloat.h"

NBTFloat::NBTFloat(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	//ignore float
	br.read();
	br.read();
	br.read();
	br.read();
}

NBTFloat::~NBTFloat(){

}

