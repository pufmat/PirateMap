#ifndef MINECRAFTREGION_H_
#define MINECRAFTREGION_H_

#include "byte.h"
#include "nbt/NBTTag.h"

#include <fstream>
#include <functional>
#include <vector>

class MinecraftRegion{
private:
	std::ifstream stream;

public:
	MinecraftRegion(const std::string&);

	void getChunks(std::function<void(const std::unique_ptr<NBTTag>&)>);

	virtual ~MinecraftRegion();
};

#endif
