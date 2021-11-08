#ifndef PIRATEMAP_H_
#define PIRATEMAP_H_

#include "Canvas.h"
#include "BlockType.h"

#include <string>

class PirateMap{
private:
	Canvas canvas;

	std::string worldDirectory;

	std::unique_ptr<Format> format;

public:
	PirateMap(const std::string&, const std::string&, std::unique_ptr<Format>);

	void start();

	void processBlock(int, int, int, uint_least32_t, BlockType);

	void updateBottomTriangles(int, int, int, uint_least32_t);
	void updateAllTriangles(int, int, int, uint_least32_t);

	bool updateTopRightTriangle(int, int, int, uint_least32_t);
	void updateTopLeftTriangle(int, int, int, uint_least32_t);
	void updateMiddleRightTriangle(int, int, int, uint_least32_t);
	void updateMiddleLeftTriangle(int, int, int, uint_least32_t);
	void updateBottomRightTriangle(int, int, int, uint_least32_t);
	void updateBottomLeftTriangle(int, int, int, uint_least32_t);

	virtual ~PirateMap();
};

#endif
