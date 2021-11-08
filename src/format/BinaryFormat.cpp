#include "BinaryFormat.h"

#include <algorithm>
#include <fstream>

BinaryFormat::BinaryFormat(){

}

void BinaryFormat::save(const std::unique_ptr<Piece>& piece){
	std::ofstream stream(piece->outputDirectory + std::to_string(piece->position.x) + "_" + std::to_string(piece->position.y) + ".bin");

	std::vector<uint_least32_t> palette;
	palette.push_back(0xffffffff); // transparent

	for(int x = 0; x < piece->width; x++){
		for(int y = 0; y < piece->height + 1; y++){

			Triangle* triangle = piece->triangles[x][y].get();
			if(triangle->depth == std::numeric_limits<int>::max()){
				continue;
			}

			if(std::find(palette.begin(), palette.end(), triangle->color) == palette.end()){
				palette.push_back(triangle->color);
			}

		}
	}

	std::size_t imageSize = piece->height;
	do{
		unsigned char tmp = imageSize & 0b01111111;
		imageSize >>= 7;
		if(imageSize != 0){
			tmp |= 0b10000000;
		}
		stream << tmp;
	}while(imageSize != 0);


	std::size_t paletteSize = palette.size() - 1; //-1 to skip transparent
	do{
		unsigned char tmp = paletteSize & 0b01111111;
		paletteSize >>= 7;
		if(paletteSize != 0){
			tmp |= 0b10000000;
		}
		stream << tmp;
	}while(paletteSize != 0);


	for(uint_least32_t color : palette){
		if(color == 0xffffffff){
			continue;
		}
		stream << static_cast<unsigned char>((color >> 16) & 0xff);
		stream << static_cast<unsigned char>((color >> 8) & 0xff);
		stream << static_cast<unsigned char>(color & 0xff);
	}


	std::size_t paletteMaxIndex = palette.size() - 1;
	int bytesPerColor = 0;
	while(paletteMaxIndex > 0){
		bytesPerColor++;
		paletteMaxIndex >>= 8;
	}

	for(int y = 0; y < piece->height + 1; y++){
		for(int x = 0; x < piece->width; x++){

			Triangle* triangle = piece->triangles[x][y].get();
			if(triangle->depth == std::numeric_limits<int>::max()){

				for(int i = 0; i < bytesPerColor; i++){
					stream << static_cast<unsigned char>(0);
				}

			}else{

				auto result = std::find(palette.begin(), palette.end(), triangle->color);
				std::size_t colorIndex = result - palette.begin();

				for(int i = 0; i < bytesPerColor; i++){
					stream << static_cast<unsigned char>(colorIndex & 0xff);
					colorIndex >>= 8;
				}

			}

		}
	}
}

BinaryFormat::~BinaryFormat(){

}

