#include "NBTCompound.h"

NBTCompound::NBTCompound(BufferedReader& br, bool noName) : NBTNamed(br, noName){
	while(true){
		std::unique_ptr<NBTTag> tag = NBTTag::parse(br);
		NBTNamed* namedPtr = dynamic_cast<NBTNamed*>(tag.get());
		if(!namedPtr){
			break;
		}
		tag.release();
		data[namedPtr->name] = std::unique_ptr<NBTNamed>(namedPtr);
	}
}

NBTCompound::~NBTCompound(){

}

