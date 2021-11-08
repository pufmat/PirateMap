#ifndef FORMAT_H_
#define FORMAT_H_

#include "Piece.h"

class Format{
public:
	Format();

	virtual void save(const std::unique_ptr<Piece>&) = 0;

	virtual ~Format();
};

#endif
