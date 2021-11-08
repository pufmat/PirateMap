#include "PirateMap.h"
#include "format/SVGFormat.h"
#include "format/BinaryFormat.h"

#include <filesystem>

int main(int argc, char** argv){
	if(argc == 4){
		std::filesystem::create_directories(argv[2]);
		std::string formatName(argv[3]);

		std::unique_ptr<Format> format;
		if(formatName == "svg"){
			format = std::make_unique<SVGFormat>();
		}else if(formatName == "binary"){
			format = std::make_unique<BinaryFormat>();
		}else{
			return 1;
		}

		PirateMap pm(argv[1], argv[2], std::move(format));
		pm.start();
		return 0;
	}else{
		return 1;
	}
}
