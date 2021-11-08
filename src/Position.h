#ifndef POSITION_H_
#define POSITION_H_

#include <cstdlib>

class Position{
public:
	int x;
	int y;

	Position(int, int);

	bool operator==(const Position&) const;

	virtual ~Position();
};

struct PositionHash{
	std::size_t operator()(const Position& p) const{
		return p.x * 31 + p.y;
	}
};

#endif
