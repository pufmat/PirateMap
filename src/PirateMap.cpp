#include "PirateMap.h"

#include "mc/MinecraftWorld.h"

#include "mc/nbt/NBTCompound.h"
#include "mc/nbt/NBTInt.h"

#include "Canvas.h"

#include <chrono>
#include <fstream>
#include <unordered_map>
#include <exception>
#include <iostream>

PirateMap::PirateMap(const std::string& worldDirectory, const std::string& outputDirectory, std::unique_ptr<Format> format) : canvas(outputDirectory, 256), format(std::move(format)){
	this->worldDirectory = worldDirectory;
}

void PirateMap::start(){
	MinecraftWorld world(this->worldDirectory);

	std::unordered_map<std::string, std::pair<int_least32_t, BlockType>> palette;

	std::ifstream fileStream("palette.csv");
	std::string line;
	while(std::getline(fileStream, line)){
		std::istringstream stringStream(line);

		std::string name;
		std::getline(stringStream, name, ',');

		int_least32_t color;
		stringStream >> color;
		stringStream.ignore(1);

		std::string type;
		std::getline(stringStream, type, ',');

		palette[name] = std::make_pair(color, type == "FULL" ? BlockType::FULL : BlockType::THIN);
	}

	std::cout << "Processing..." << std::endl;

	std::chrono::time_point start = std::chrono::high_resolution_clock::now();

	world.getBlocks([this, &palette](int x, int y, int z, const std::string& name){
		try{
			const std::pair<const int_least32_t, const BlockType>& pair = palette.at(name);
			if(pair.first != -1){
				processBlock(x, y, z, static_cast<uint_least32_t>(pair.first), pair.second);
			}
		}catch(const std::exception& ex){
			std::cout << "Missing block in palette: " << name << std::endl;
		}
	});

	std::cout << "Done in " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count()) << "ms!" << std::endl;


	std::cout << "Saving..." << std::endl;

	start = std::chrono::high_resolution_clock::now();

	canvas.save(format);

	std::cout << "Done in " << (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count()) << "ms!" << std::endl;
}

void PirateMap::processBlock(int x, int y, int z, uint_least32_t color, BlockType type){
	switch(type){
	case BlockType::FULL:
		updateAllTriangles(x, y, z, color);
		break;
	case BlockType::THIN:
		updateBottomTriangles(x, y, z, color);
		break;
	default:
		break;
	}
}

void PirateMap::updateBottomTriangles(int voxelX, int voxelY, int voxelZ, uint_least32_t color){
	int gridX = voxelX - voxelZ;
	int gridY = voxelX + voxelZ - voxelY * 2;
	int depth = -(voxelX + voxelY + voxelZ);

	updateBottomRightTriangle(gridX, gridY, depth, color);
	updateBottomLeftTriangle(gridX, gridY, depth, color);
}

void PirateMap::updateAllTriangles(int voxelX, int voxelY, int voxelZ, uint_least32_t color){
	int gridX = voxelX - voxelZ;
	int gridY = voxelX + voxelZ - voxelY * 2;
	int depth = -(voxelX + voxelY + voxelZ);

	if(updateTopRightTriangle(gridX, gridY, depth, color)){
		return;
	}

	int r = (color >> 16) & 0xff;
	int g = (color >> 8) & 0xff;
	int b = color & 0xff;

	int color1 = ((r * 86 / 100) << 16) | ((g * 86 / 100) << 8) | (b * 86 / 100);
	int color2 = ((r * 80 / 100) << 16) | ((g * 80 / 100) << 8) | (b * 80 / 100);

	updateTopLeftTriangle(gridX, gridY, depth, color);
	updateMiddleRightTriangle(gridX, gridY, depth, color2);
	updateMiddleLeftTriangle(gridX, gridY, depth, color1);
	updateBottomRightTriangle(gridX, gridY, depth, color2);
	updateBottomLeftTriangle(gridX, gridY, depth, color1);
}

bool PirateMap::updateTopRightTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	return canvas.updateTriangle(gridX, gridY, depth, color, true);
}

void PirateMap::updateTopLeftTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	canvas.updateTriangle(gridX - 1, gridY, depth, color, false);
}

void PirateMap::updateMiddleRightTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	canvas.updateTriangle(gridX, gridY + 1, depth, color, false);
}

void PirateMap::updateMiddleLeftTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	canvas.updateTriangle(gridX - 1, gridY + 1, depth, color, false);
}

void PirateMap::updateBottomRightTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	canvas.updateTriangle(gridX, gridY + 2, depth, color, false);
}

void PirateMap::updateBottomLeftTriangle(int gridX, int gridY, int depth, uint_least32_t color){
	canvas.updateTriangle(gridX - 1, gridY + 2, depth, color, false);
}

PirateMap::~PirateMap(){

}

