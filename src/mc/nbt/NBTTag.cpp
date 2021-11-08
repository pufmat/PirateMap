#include "NBTTag.h"

#include "NBTEnd.h"
#include "NBTByte.h"
#include "NBTShort.h"
#include "NBTInt.h"
#include "NBTLong.h"
#include "NBTFloat.h"
#include "NBTDouble.h"
#include "NBTByteArray.h"
#include "NBTString.h"
#include "NBTList.h"
#include "NBTCompound.h"
#include "NBTIntArray.h"
#include "NBTLongArray.h"

std::unique_ptr<NBTTag> NBTTag::parse(BufferedReader& br){
	byte type = br.read();
	return create(br, type, false);
}

std::unique_ptr<NBTTag> NBTTag::create(BufferedReader& br, byte type, bool noName){
	switch(type){
	case 0:
		return std::make_unique<NBTEnd>(br);
	case 1:
		return std::make_unique<NBTByte>(br, noName);
	case 2:
		return std::make_unique<NBTShort>(br, noName);
	case 3:
		return std::make_unique<NBTInt>(br, noName);
	case 4:
		return std::make_unique<NBTLong>(br, noName);
	case 5:
		return std::make_unique<NBTFloat>(br, noName);
	case 6:
		return std::make_unique<NBTDouble>(br, noName);
	case 7:
		return std::make_unique<NBTByteArray>(br, noName);
	case 8:
		return std::make_unique<NBTString>(br, noName);
	case 9:
		return std::make_unique<NBTList>(br, noName);
	case 10:
		return std::make_unique<NBTCompound>(br, noName);
	case 11:
		return std::make_unique<NBTIntArray>(br, noName);
	case 12:
		return std::make_unique<NBTLongArray>(br, noName);
	}

	return std::make_unique<NBTTag>();
}

NBTTag::NBTTag(){

}

NBTTag::~NBTTag(){

}

