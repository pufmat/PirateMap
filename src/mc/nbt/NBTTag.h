#ifndef NBTTAG_H_
#define NBTTAG_H_

#include "mc/BufferedReader.h"

#include <memory>

class NBTTag{
public:
	static std::unique_ptr<NBTTag> parse(BufferedReader&);
	static std::unique_ptr<NBTTag> create(BufferedReader&, byte, bool);

	NBTTag();

	virtual ~NBTTag();
};

#endif
