#include <cassert>
#include <algorithm>
#include <array>

#include "WorldLoader.h"
#include "Log.h"

std::vector<std::string> Tokenize(const std::string& string, std::string_view delims) {
	std::vector<std::string> parts{};
	for (auto beg = string.find_first_not_of(delims); beg != std::string::npos;) {
		auto end = string.find_first_of(delims, beg);
		parts.emplace_back(string.substr(beg, end - beg));
		beg = string.find_first_not_of(delims, end);
	}
	return parts;
}

std::array<float, 3> ParseFloat3(const std::string& string, std::string_view delims) {
	std::array<float, 3> res{};
	const auto parts = Tokenize(string, delims);
	assert(parts.size() == 3 && "Wrong float3 format");
	std::transform(parts.begin(), parts.end(), res.begin(), [](auto str) { return std::stof(str); });
	return res;
}

std::array<float, 4> ParseFloat4(const std::string& string, std::string_view delims) {
	std::array<float, 4> res{};
	const auto parts = Tokenize(string, delims);
	assert(parts.size() == 4 && "Wrong float4 format");
	std::transform(parts.begin(), parts.end(), res.begin(), [](auto str) { return std::stof(str); });
	return res;
}

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

void WorldLoader::ParseEntities(flecs::world& ecs, std::string_view world_path)
{
	const auto world = WorldLoader::LoadXML(world_path);

	for (const auto& entity : world->child("entities"))
	{
		assert(entity && "Corrupt file");
		auto e = ecs.entity();

		for (const auto& child : entity.children())
		{
			if (sections.find(child.name()) != sections.end())
			{
				for (const auto& attr : child.attributes())
				{
					const auto& componentsInSection = sections.at(child.name());
					const auto component = componentMap.at(attr.name());
					if (componentsInSection.find(component) == componentsInSection.end())
					{
						LogZA("Unexpected component in section %s\n", child.name());
						continue;
					}
					// Add entity component
					AddComponent(e, component, attr);

				}
			}
			else if (componentMap.find(child.name()) != componentMap.end())
			{
				const auto component = componentMap.at(child.name());
				AddComponent(e, component, child);
			}
			else
			{
				LogZA("Unexpected entry in document\n");
			}
		}
	}
}

void WorldLoader::AddComponent(flecs::entity e, EntityComponent comp, const pugi::xml_node& node)
{
	switch (comp)
	{
	case eGun:
		LogZA("Adding gun : %s, %f, %d, %d, %f\n", node.attribute("ammo").value(), node.attribute("reload_time").as_float(),
			static_cast<uint16_t>(node.attribute("num_rounds").as_uint()),
			static_cast<uint16_t>(node.attribute("capacity").as_uint()),
			node.attribute("muzzle_speed").as_float());
		e.set(
			Gun{
				node.attribute("ammo").value(),
				node.attribute("reload_time").as_float(),
				static_cast<uint16_t>(node.attribute("num_rounds").as_uint()),
				static_cast<uint16_t>(node.attribute("capacity").as_uint()),
				node.attribute("muzzle_speed").as_float()
			}
		);
		break;
	case eCubeMesh:
		LogZA("Adding cubemesh");
		e.add<CubeMesh>();
		break;
	case eScripts:
	{
		LogZA("Adding scripts\n");
		auto scripts = Tokenize(node.attribute("filenames").value(), ",");
		std::transform(scripts.begin(), scripts.end(), scripts.begin(), [](auto str) { return SCRIPT_DIR + str; });
		for (const auto& scr : scripts) {
			LogZA("%s\n", scr.c_str());
		}
		e.set(
			ScriptProxies{
				scripts
			}
		);
	}
	break;
	}
}

void WorldLoader::AddComponent(flecs::entity e, EntityComponent comp, const pugi::xml_attribute& attr)
{
	switch (comp)
	{
	case ePosition:
		LogZA("Adding position\n");
		e.set(
			Position{ ParseFloat3(attr.value(), ",") }
		);
		break;
	case eScale:
		LogZA("Adding scale\n");
		e.set(
			Scale{ attr.as_float() }
		);
		break;
	case eVelocity:
		LogZA("Adding velocity\n");
		e.set(
			Velocity{ ParseFloat3(attr.value(), ",") }
		);
		break;
	case eBouncePlane:
		LogZA("Adding bounceplane\n");
		e.set(
			BouncePlane{ ParseFloat4(attr.value(), ",") }
		);
		break;
	case eBounciness:
		LogZA("Adding bounciness\n");
		e.set(
			Bounciness{ attr.as_float() }
		);
		break;
	case eFrictionAmount:
		LogZA("Adding friction amount\n");
		e.set(
			FrictionAmount{ attr.as_float() }
		);
		break;
	case eGravity:
		LogZA("Adding gravity : %f\n", ParseFloat3(attr.value(), ",")[1]);
		e.set(
			Gravity{ ParseFloat3(attr.value(), ",") }
		);
		break;
	}
}