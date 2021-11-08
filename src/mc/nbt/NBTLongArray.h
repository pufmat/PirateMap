#ifndef NBTLONGARRAY_H_
#define NBTLONGARRAY_H_

#include "NBTNamed.h"

#include <vector>

class NBTLongArray: public NBTNamed{
public:
	std::vector<uint_least64_t> data;

	NBTLongArray(BufferedReader&, bool);

	virtual ~NBTLongArray();
};

#endif
