#include "Position.h"

Position::Position(int x, int y){
	this->x = x;
	this->y = y;
}

bool Position::operator==(const Position& pos) const{
	return this->x == pos.x && this->y == pos.y;
}

Position::~Position(){

}

