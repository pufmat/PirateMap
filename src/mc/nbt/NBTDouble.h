#ifndef NBTDOUBLE_H_
#define NBTDOUBLE_H_

#include "NBTNamed.h"

class NBTDouble: public NBTNamed{
public:
	NBTDouble(BufferedReader&, bool);

	virtual ~NBTDouble();
};

#endif
