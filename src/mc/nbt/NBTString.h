#ifndef NBTSTRING_H_
#define NBTSTRING_H_

#include "NBTNamed.h"

class NBTString: public NBTNamed{
public:
	std::string data;

	NBTString(BufferedReader&, bool);

	virtual ~NBTString();
};

#endif
