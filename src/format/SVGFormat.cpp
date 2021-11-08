#include "SVGFormat.h"

#include <string>
#include <unordered_map>
#include <fstream>

SVGFormat::SVGFormat(){

}

static char table[] = {
		'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'
};
inline void toHex(std::string& string, uint_least8_t value){
	if(value < 16){
		string += table[0];
		string += table[value];
	}else{
		string += table[(value >> 4) & 0x0f];
		string += table[value & 0x0f];
	}
}

void SVGFormat::save(const std::unique_ptr<Piece>& piece){
	std::unordered_map<uint_least32_t, std::string> paths;

	for(int x = 0; x < piece->width; x++){
		for(int y = 0; y < piece->height + 1; y++){

			Triangle* triangle = piece->triangles[x][y].get();
			if(triangle->depth == std::numeric_limits<int>::max()){
				continue;
			}

			std::string path;

			if(((x + y) & 0x01) == 0){
				path.append("M");
				path.append(std::to_string(x * 2));
				path.append(",");
				path.append(std::to_string(y - 1));
				path.append("v2");
				path.append("l2,-1");
				path.append("z");
			}else{
				path.append("M");
				path.append(std::to_string(x * 2));
				path.append(",");
				path.append(std::to_string(y));
				path.append("l2,-1");
				path.append("v2");
				path.append("z");
			}

			paths[triangle->color] += path;

		}
	}

	std::string svg;
	svg.append("<svg viewBox=\"0 0 ");
	svg.append(std::to_string(piece->width * 2));
	svg.append(" ");
	svg.append(std::to_string(piece->height));
	svg.append("\" xmlns=\"http://www.w3.org/2000/svg\">");

	for(const std::pair<const uint_least32_t, std::string>& pair : paths){
		uint_least32_t color = pair.first;
		const std::string& path = pair.second;

		svg.append("<path d=\"");
		svg.append(path);
		svg.append("\" ");

		svg.append("fill=\"#");
		toHex(svg, (color >> 16) & 0xff);
		toHex(svg, (color >> 8) & 0xff);
		toHex(svg, color & 0xff);
		svg.append("\" ");

		svg.append("shape-rendering=\"crispEdges\" />");
	}

	svg.append("</svg>");

	std::ofstream stream(piece->outputDirectory + std::to_string(piece->position.x) + "_" + std::to_string(piece->position.y) + ".svg");
	stream << svg;
}

SVGFormat::~SVGFormat(){

}

