#ifndef PIECE_H_
#define PIECE_H_

#include "Position.h"
#include "Triangle.h"

#include <cstdint>
#include <vector>
#include <string>
#include <memory>

class Piece{
public:
	std::vector<std::vector<std::unique_ptr<Triangle>>> triangles;

	std::string outputDirectory;

	Position position;

	int width;
	int height;

	Piece(const std::string&, const Position&, int, int);

	bool updateTriangle(int, int, int, uint_least32_t, bool);

	virtual ~Piece();
};

#endif
