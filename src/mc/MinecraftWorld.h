#ifndef MINECRAFTWORLD_H_
#define MINECRAFTWORLD_H_

#include <string>
#include <functional>
#include <filesystem>

class MinecraftWorld{
private:
	std::filesystem::path directory;
	bool nether;

public:
	MinecraftWorld(const std::string&);

	void getBlocks(std::function<void(int, int, int, const std::string&)>);

	virtual ~MinecraftWorld();
};

#endif
