#include "NBTDouble.h"

NBTDouble::NBTDouble(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	//ignore double
	br.read();
	br.read();
	br.read();
	br.read();
	br.read();
	br.read();
	br.read();
	br.read();
}

NBTDouble::~NBTDouble(){

}

