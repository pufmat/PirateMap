#include "MinecraftRegion.h"

#include "BufferedReader.h"
#include "nbt/NBTTag.h"

#include <algorithm>
#include <stdexcept>
#include <zlib.h>
#include <iostream>

static const int BUFFER_SIZE = 2048;

MinecraftRegion::MinecraftRegion(const std::string& path){
	stream.open(path);
}

void MinecraftRegion::getChunks(std::function<void(const std::unique_ptr<NBTTag>&)> callback){
	std::vector<uint_least32_t> locations;

	byte buffer[BUFFER_SIZE];

	for(int i = 0; i < 32 * 32; ++i){
		stream.read(reinterpret_cast<char*>(buffer), 4);
		uint_least32_t location = (static_cast<uint_least32_t>(buffer[0]) << 16) | (static_cast<uint_least32_t>(buffer[1]) << 8) | static_cast<uint_least32_t>(buffer[2]);
		char size = buffer[3];
		if(size > 0){
			locations.push_back(location * 4096);
		}
	}

	//ignore timestamps
	stream.ignore(4096);

	std::sort(locations.begin(), locations.end(), std::less<uint_least32_t>());

	uint_least32_t read = 2 * 4096;

	for(uint_least32_t location : locations){
		//jump to location
		stream.ignore(location - read);
		read = location;

		stream.read(reinterpret_cast<char*>(buffer), 5);

		uint_least32_t compressedSize = (static_cast<uint_least32_t>(buffer[0]) << 24) | (static_cast<uint_least32_t>(buffer[1]) << 16) | (static_cast<uint_least32_t>(buffer[2]) << 8) | static_cast<uint_least32_t>(buffer[3]);

		compressedSize -= 1;
		byte compressionType = buffer[4];

		if(compressionType != 2){
			throw std::runtime_error("Unknown compression type!");
		}else{
			std::unique_ptr<byte[]> compressedBuffer(new byte[compressedSize]);
			stream.read(reinterpret_cast<char*>(compressedBuffer.get()), compressedSize);

			z_stream infstream;
			infstream.zalloc = Z_NULL;
			infstream.zfree = Z_NULL;
			infstream.opaque = Z_NULL;

			infstream.avail_in = compressedSize;
			infstream.next_in = compressedBuffer.get();

			inflateInit(&infstream);

			BufferedReader br([&infstream, &br, &buffer](){
				infstream.avail_out = BUFFER_SIZE;
				infstream.next_out = buffer;
				if(inflate(&infstream, Z_NO_FLUSH) != Z_OK){
					//throw std::runtime_error("Decompression error!");
				}
				br.setBuffer(buffer, BUFFER_SIZE - infstream.avail_out);
			});

			callback(NBTTag::parse(br));

			inflateEnd(&infstream);

		}

		read += 4 + 1 + compressedSize;

	}

}

MinecraftRegion::~MinecraftRegion(){

}

