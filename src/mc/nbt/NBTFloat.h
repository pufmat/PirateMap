#ifndef NBTFLOAT_H_
#define NBTFLOAT_H_

#include "NBTNamed.h"

class NBTFloat: public NBTNamed{
public:
	NBTFloat(BufferedReader&, bool);

	virtual ~NBTFloat();
};

#endif
