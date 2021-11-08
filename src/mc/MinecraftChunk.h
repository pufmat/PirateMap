#ifndef MINECRAFTCHUNK_H_
#define MINECRAFTCHUNK_H_

#include "nbt/NBTCompound.h"

#include <array>
#include <functional>
#include <memory>
#include <string>

class MinecraftChunk{
public:
	std::array<NBTCompound*, 16> sectionsPointers;

	int chunkX;
	int chunkZ;

	bool ready;

	MinecraftChunk(const std::unique_ptr<NBTTag>&);

	void getBlocks(const std::function<void(int, int, int, const std::string&)>&);

	virtual ~MinecraftChunk();
};

#endif
