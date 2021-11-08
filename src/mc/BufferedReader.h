#ifndef BUFFEREDREADER_H_
#define BUFFEREDREADER_H_

#include "byte.h"

#include <functional>
#include <vector>

class BufferedReader{
private:
	std::function<void()> request;

	byte* buffer;
	std::size_t size;

	std::size_t cursor;

public:
	BufferedReader(std::function<void()>);

	void setBuffer(byte*, std::size_t);

	byte read();

	virtual ~BufferedReader();
};

#endif /* BUFFEREDREADER_H_ */
