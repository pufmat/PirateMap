#ifndef CANVAS_H_
#define CANVAS_H_

#define USE_TBB

#include "Position.h"
#include "Piece.h"
#include "format/Format.h"

#include <memory>

#ifdef USE_TBB
#include <tbb/concurrent_unordered_map.h>
#else
#include <shared_mutex>
#include <unordered_map>
#endif

class Canvas{
private:

#ifdef USE_TBB
	tbb::concurrent_unordered_map<Position, std::unique_ptr<Piece>, PositionHash> map;
#else
	std::array<std::pair<std::shared_mutex, std::unordered_map<Position, std::unique_ptr<Piece>, PositionHash>>, 8192> maps;
#endif

	std::string outputDirectory;

	int pieceWidth;
	int pieceHeight;

	Piece* getOrCreatePiece(int, int);

public:
	Canvas(const std::string&, int);

	bool updateTriangle(int, int, int, uint_least32_t, bool);
	void save(const std::unique_ptr<Format>&);

	virtual ~Canvas();
};

#endif
