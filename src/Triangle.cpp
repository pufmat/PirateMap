#include "Triangle.h"

#include <limits>

Triangle::Triangle(){
	depth = std::numeric_limits<int>::max();
	masterDepth = std::numeric_limits<int>::max();
	color = 0x000000;
}

Triangle::~Triangle(){

}

