#ifndef NBTINTARRAY_H_
#define NBTINTARRAY_H_

#include "NBTNamed.h"

#include <vector>

class NBTIntArray: public NBTNamed{
public:
	std::vector<uint_least32_t> data;

	NBTIntArray(BufferedReader&, bool);

	virtual ~NBTIntArray();
};

#endif
