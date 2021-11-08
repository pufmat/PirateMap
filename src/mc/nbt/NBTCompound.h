#ifndef NBTCOMPOUND_H_
#define NBTCOMPOUND_H_

#include "NBTNamed.h"

#include <unordered_map>

class NBTCompound : public NBTNamed{
public:
	std::unordered_map<std::string, std::unique_ptr<NBTTag>> data;

	NBTCompound(BufferedReader&, bool);

	virtual ~NBTCompound();
};

#endif
