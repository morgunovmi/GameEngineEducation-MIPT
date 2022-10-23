#pragma once

#include <string_view>
#include <tinyxml2.h>

class WorldLoader {
public:
	static tinyxml2::XMLDocument LoadXML(std::string_view path);
};
