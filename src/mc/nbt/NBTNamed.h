#ifndef NBTNAMED_H_
#define NBTNAMED_H_

#include "NBTTag.h"

#include <string>

class NBTNamed : public NBTTag{
public:
	std::string name;

	NBTNamed();
	NBTNamed(BufferedReader&, bool);

	virtual ~NBTNamed();
};

#endif
