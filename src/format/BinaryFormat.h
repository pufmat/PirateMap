#ifndef BINARYFORMAT_H_
#define BINARYFORMAT_H_

#include "Format.h"

class BinaryFormat: public Format{
public:
	BinaryFormat();

	void save(const std::unique_ptr<Piece>&);

	virtual ~BinaryFormat();
};

#endif
