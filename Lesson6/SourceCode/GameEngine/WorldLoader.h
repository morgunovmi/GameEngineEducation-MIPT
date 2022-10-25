#pragma once

#include <string_view>
#include <memory>
#include <pugixml.hpp>
#include <flecs.h>

#include "EntitySystem/Components.h"

const std::string SCRIPT_DIR{ "../../../Assets/scripts/" };

class WorldLoader {
public:
	static std::shared_ptr<pugi::xml_document> LoadXML(std::string_view path);
	static void ParseEntities(flecs::world& ecs, std::string_view world_path);
	static void AddComponent(flecs::entity e, EntityComponent comp, const pugi::xml_node& node);
	static void AddComponent(flecs::entity e, EntityComponent comp, const pugi::xml_attribute& attr);	
};