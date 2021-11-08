#include "MinecraftChunk.h"

#include "nbt/NBTCompound.h"
#include "nbt/NBTList.h"
#include "nbt/NBTString.h"
#include "nbt/NBTInt.h"
#include "nbt/NBTByte.h"
#include "nbt/NBTLongArray.h"

#include <cmath>
//#include <bit>

MinecraftChunk::MinecraftChunk(const std::unique_ptr<NBTTag>& rootTag){
	NBTCompound* root = reinterpret_cast<NBTCompound*>(rootTag.get());
	NBTCompound* level = reinterpret_cast<NBTCompound*>(root->data.at("Level").get());
	NBTList* sections = reinterpret_cast<NBTList*>(level->data.at("Sections").get());

	for(int i = 0; i < 16; ++i){
		sectionsPointers[i] = nullptr;
	}

	for(const std::unique_ptr<NBTTag>& sectionTag : sections->data){
		NBTCompound* section = reinterpret_cast<NBTCompound*>(sectionTag.get());
		if(section){
			int sectionY = reinterpret_cast<NBTByte*>(section->data.at("Y").get())->data;
			if(sectionY >= 0 && sectionY <= 15){
				sectionsPointers[sectionY] = section;
			}
		}
	}

	NBTInt* xPos = reinterpret_cast<NBTInt*>(level->data.at("xPos").get());
	chunkX = xPos->data;

	NBTInt* zPos = reinterpret_cast<NBTInt*>(level->data.at("zPos").get());
	chunkZ = zPos->data;

	NBTString* status = reinterpret_cast<NBTString*>(level->data.at("Status").get());
	ready = status->data == "full";
}

void MinecraftChunk::getBlocks(const std::function<void(int, int, int, const std::string&)>& callback){
	for(int sectionY = 0; sectionY < 16; ++sectionY){
		NBTCompound* section = sectionsPointers[sectionY];
		if(section == nullptr){
			continue;
		}

		auto blockStatesResult = section->data.find("BlockStates");
		if(blockStatesResult == section->data.end()){
			continue;
		}

		NBTLongArray* blockStates = reinterpret_cast<NBTLongArray*>(blockStatesResult->second.get());

		NBTList* palette = reinterpret_cast<NBTList*>(section->data["Palette"].get());

		std::size_t value = palette->data.size() - 1;
		//int bits = std::bit_width(value);
		int bits = 0;
		while(value > 0){
			bits++;
			value >>= 1;
		}
		if(bits < 4){
			bits = 4;
		}

		std::vector<std::string> names;
		for(const std::unique_ptr<NBTTag>& blockTag : palette->data){
			NBTCompound* block = reinterpret_cast<NBTCompound*>(blockTag.get());
			names.push_back(reinterpret_cast<NBTString*>(block->data["Name"].get())->data);
		}

		for(int sy = 0; sy < 16; ++sy){
			int y = sectionY * 16 + sy;

			for(int x = 0; x < 16; ++x){
				for(int z = 0; z < 16; ++z){

					int index = sy * 16 * 16 + z * 16 + x;

					int state = (index / (64 / bits));


					uint_least64_t data = blockStates->data[state];

					uint_least64_t shifted_data = data >> ((index % (64 / bits)) * bits);

					uint_least64_t palette_id = shifted_data & ((2 << (bits - 1)) - 1);

					if(palette->data.size() <= palette_id){
						continue;
					}

					const std::string& name = names[palette_id];

					callback(chunkX * 16 + x, y, chunkZ * 16 + z, name);
				}
			}
		}
	}
}

MinecraftChunk::~MinecraftChunk(){

}

