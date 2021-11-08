#ifndef NBTBYTE_H_
#define NBTBYTE_H_

#include "NBTNamed.h"

class NBTByte : public NBTNamed{
public:
	byte data;

	NBTByte(BufferedReader&, bool);

	virtual ~NBTByte();
};

#endif
