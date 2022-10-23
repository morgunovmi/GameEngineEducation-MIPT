#pragma once

#include <string_view>
#include <memory>
#include <pugixml.hpp>

class WorldLoader {
public:
	static std::shared_ptr<pugi::xml_document> LoadXML(std::string_view path);
};
