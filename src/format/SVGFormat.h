#ifndef SVGFORMAT_H_
#define SVGFORMAT_H_

#include "Format.h"

class SVGFormat: public Format{
public:
	SVGFormat();

	void save(const std::unique_ptr<Piece>&);

	virtual ~SVGFormat();
};

#endif
