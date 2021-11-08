#ifndef NBTEND_H_
#define NBTEND_H_

#include "NBTTag.h"

class NBTEnd : public NBTTag{
public:
	NBTEnd(BufferedReader&);

	virtual ~NBTEnd();
};

#endif
