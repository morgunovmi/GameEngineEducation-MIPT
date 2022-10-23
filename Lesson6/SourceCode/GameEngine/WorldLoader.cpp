#include "WorldLoader.h"

#include <cassert>

std::shared_ptr<pugi::xml_document> WorldLoader::LoadXML(std::string_view path)
{
	auto doc = std::make_shared<pugi::xml_document>();
	pugi::xml_parse_result result = doc->load_file(path.data());
	if (!result)
	{
		assert(0 && "Couldn't parse xml");
	}
	
	return doc;
}