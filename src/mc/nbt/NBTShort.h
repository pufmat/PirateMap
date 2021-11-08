#ifndef NBTSHORT_H_
#define NBTSHORT_H_

#include "NBTNamed.h"

class NBTShort : public NBTNamed{
public:
	uint_least16_t data;

	NBTShort(BufferedReader&, bool);

	virtual ~NBTShort();
};

#endif
