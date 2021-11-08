#include "Piece.h"

Piece::Piece(const std::string& outputDirectory, const Position& p, int width, int height) : position(p){
	this->outputDirectory = outputDirectory;

	this->width = width;
	this->height = height;

	this->triangles.resize(width);
	for(int i = 0; i < width; ++i){
		for(int j = 0; j < height + 1; ++j){
			this->triangles[i].push_back(std::make_unique<Triangle>());
		}
	}
}

bool Piece::updateTriangle(int x, int y, int depth, uint_least32_t color, bool isMaster){
	Triangle* triangle = triangles[x][y].get();

	std::scoped_lock<std::mutex> lock(triangle->mutex);
	if(triangle->depth > depth){
		triangle->depth = depth;
		triangle->color = color;
		if(isMaster){
			triangle->masterDepth = depth;
		}
	}else if(isMaster){
		if(triangle->masterDepth > depth){
			triangle->masterDepth = depth;
		}else{
			return true;
		}
	}
	return false;
}

Piece::~Piece(){

}
