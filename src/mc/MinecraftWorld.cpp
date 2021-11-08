#include "MinecraftWorld.h"

#include "MinecraftRegion.h"
#include "MinecraftChunk.h"

#include <vector>
#include <queue>
#include <thread>
#include <iostream>
#include <atomic>
#include <mutex>

MinecraftWorld::MinecraftWorld(const std::string& path){
	directory = std::filesystem::path(path) / "region";
	nether = false;

	if(!std::filesystem::exists(directory)){
		directory = std::filesystem::path(path) / "DIM1" / "region";
	}
	if(!std::filesystem::exists(directory)){
		directory = std::filesystem::path(path) / "DIM-1" / "region";
		nether = true;
	}

	if(!std::filesystem::exists(directory)){
		throw std::runtime_error("Could not find region files!");
	}
}

void MinecraftWorld::getBlocks(std::function<void(int, int, int, const std::string&)> callback){
	unsigned int threadsCount = std::max(1u, std::thread::hardware_concurrency());

	std::queue<std::string> tasks;

	unsigned int regionCount = 0;
	for(const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(directory)){
		tasks.push(entry.path());
		regionCount++;
	}

	bool nether = this->nether;

	std::function<void(const std::unique_ptr<NBTTag>&)> regionCallback = [&callback, nether](const std::unique_ptr<NBTTag>& tag){
		MinecraftChunk chunk(tag);
		if(chunk.ready){
			if(nether){
				std::string blocks[16][256][16];
				chunk.getBlocks([&blocks, &chunk](int x, int y, int z, const std::string& block){
					blocks[x - chunk.chunkX * 16][y][z - chunk.chunkZ * 16] = block;
				});
				for(int x = 0; x < 16; ++x){
					for(int z = 0; z < 16; ++z){

						int y = 128;

						int startY = 0;
						int currentStreak = 0;

						for(int currentY = 0; currentY < 128; currentY++){
							const std::string& block = blocks[x][currentY][z];

							bool empty = false;
							if(block.empty()){
								empty = true;
							}
							if(block == "minecraft:air"){
								empty = true;
							}

							if(empty){
								if(currentStreak == 0){
									startY = currentY;
								}
								currentStreak++;
								if(currentStreak >= 8){
									y = startY;
								}
							}else{
								currentStreak = 0;
							}
						}

						while(y > 0){
							y--;
							const std::string& block = blocks[x][y][z];
							if(block.empty()){
								continue;
							}
							callback(x + chunk.chunkX * 16, y, z + chunk.chunkZ * 16, block);
						}

					}
				}
			}else{
				chunk.getBlocks(callback);
			}
		}
	};

	std::vector<std::thread> threads;

	std::atomic<int> processedCount(0);
	std::cout << "0/" << regionCount << std::flush;

	std::mutex mutex;

	for(unsigned int i = 0; i < threadsCount; ++i){
		threads.push_back(std::thread([&tasks, &mutex, regionCallback, &processedCount, regionCount](){
			while(true){
				std::unique_lock<std::mutex> lock(mutex);
				if(tasks.empty()){
					break;
				}
				std::string path = tasks.front();
				tasks.pop();
				lock.unlock();

				MinecraftRegion region(path);
				region.getChunks(regionCallback);
				std::cout << '\r' << (++processedCount) << '/' << regionCount << std::flush;
			}
		}));
	}

	for(std::thread& thread : threads){
		thread.join();
	}

	std::cout << std::endl;
}

MinecraftWorld::~MinecraftWorld(){

}

