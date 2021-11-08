#ifndef NBTINT_H_
#define NBTINT_H_

#include "NBTNamed.h"

class NBTInt: public NBTNamed{
public:
	uint_least32_t data;

	NBTInt(BufferedReader&, bool);

	virtual ~NBTInt();
};

#endif
