#ifndef NBTBYTEARRAY_H_
#define NBTBYTEARRAY_H_

#include "NBTNamed.h"

#include <vector>

class NBTByteArray: public NBTNamed{
public:
	std::vector<byte> data;

	NBTByteArray(BufferedReader&, bool);

	virtual ~NBTByteArray();
};

#endif
