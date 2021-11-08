#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cstdint>
#include <mutex>

class Triangle{
public:
	uint_least32_t color;
	int depth;
	int masterDepth;

	std::mutex mutex;

	Triangle();
	virtual ~Triangle();
};

#endif
