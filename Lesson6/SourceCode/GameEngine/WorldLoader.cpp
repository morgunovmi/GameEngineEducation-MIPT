#include "WorldLoader.h"

#include "Log.h"

tinyxml2::XMLDocument WorldLoader::LoadXML(std::string_view path)
{
	tinyxml2::XMLDocument doc{};
	doc.LoadFile(path.data());
	tinyxml2::XMLPrinter printer;
	doc.Print(&printer);
	// printer.CStr()
	LogZA("%s\n", printer.CStr());
	
	return {};
}