#include "Canvas.h"

Canvas::Canvas(const std::string& outputDirectory, int size){
	this->outputDirectory = outputDirectory;

	this->pieceWidth = size / 2;
	this->pieceHeight = size;
}

Piece* Canvas::getOrCreatePiece(int x, int y){
	Position position(x, y);

#ifdef USE_TBB

	auto result = map.find(position);
	if(result == map.end()){
		map[position] = std::make_unique<Piece>(outputDirectory, position, this->pieceWidth, this->pieceHeight);
		return map[position].get();
	}else{
		return result->second.get();
	}

#else

	std::pair<std::shared_mutex, std::unordered_map<Position, std::unique_ptr<Piece>, PositionHash>>& pair = maps[PositionHash()(position) % maps.size()];

	std::unordered_map<Position, std::unique_ptr<Piece>, PositionHash>& map = pair.second;

	std::shared_lock<std::shared_mutex> sharedLock(pair.first);

	auto result = map.find(position);
	if(result == map.end()){
		sharedLock.unlock();
		std::unique_lock<std::shared_mutex> uniqueLock(pair.first);

		map[position] = std::make_unique<Piece>(outputDirectory, position, this->pieceWidth, this->pieceHeight);
		return map[position].get();
	}else{
		return result->second.get();
	}

#endif

}

bool Canvas::updateTriangle(int gridX, int gridY, int depth, uint_least32_t color, bool master){
	int pieceX = gridX / pieceWidth;
	int pieceY = gridY / pieceHeight;
	int innerX = gridX % pieceWidth;
	int innerY = gridY % pieceHeight;

	if((innerX != 0) && (gridX < 0)){
		pieceX -= 1;
	}
	if((innerY != 0) && (gridY < 0)){
		pieceY -= 1;
	}

	if(innerX < 0){
		innerX += pieceWidth;
	}

	if(innerY < 0){
		innerY += pieceHeight;
	}

	if(innerY == 0){
		getOrCreatePiece(pieceX, pieceY - 1)->updateTriangle(innerX, pieceHeight, depth, color, false);
	}
	return getOrCreatePiece(pieceX, pieceY)->updateTriangle(innerX, innerY, depth, color, master);
}

void Canvas::save(const std::unique_ptr<Format>& format){

#ifdef USE_TBB

	for(const std::pair<const Position, std::unique_ptr<Piece>>& pair : map){
		format->save(pair.second);
	}

#else

	for(const std::pair<std::shared_mutex, std::unordered_map<Position, std::unique_ptr<Piece>, PositionHash>>& pair0 : maps){
		for(const std::pair<const Position, std::unique_ptr<Piece>>& pair1 : pair0.second){
			format->save(pair1.second);
		}
	}

#endif

}

Canvas::~Canvas(){

}

