#ifndef NBTLIST_H_
#define NBTLIST_H_

#include "NBTNamed.h"

#include <vector>

class NBTList: public NBTNamed{
public:
	std::vector<std::unique_ptr<NBTTag>> data;

	NBTList(BufferedReader&, bool noName);

	virtual ~NBTList();
};

#endif
