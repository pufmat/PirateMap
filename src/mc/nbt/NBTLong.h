#ifndef NBTLONG_H_
#define NBTLONG_H_

#include "NBTNamed.h"

class NBTLong: public NBTNamed{
public:
	uint_least64_t data;

	NBTLong(BufferedReader& br, bool);

	virtual ~NBTLong();
};

#endif
