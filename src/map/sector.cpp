#include "sector.hpp"

namespace Cryptid { namespace Map {
	using nlohmann::json;

	auto from_json(const json& j, SectorDefinition& sectorDef) -> void {
		int id = 0;
		j.at("id").get_to(id);
		sectorDef.set_id(id);

		auto jHexes = j.at("hexes");
		std::vector<Hex> hexes;
		hexes.reserve(N_HEXES_PER_SECTOR);
		for (const auto& [key, jHex] : jHexes.items()) {
			int index = std::stoi(key);
			auto terrainType = jHex.at("terrainType").get<TerrainType>();
			std::optional<AnimalTerritoryType> animalTerritoryType = std::nullopt;
			if (jHex.contains("animalTerritoryType")) {
				animalTerritoryType = jHex.at("animalTerritoryType").get<AnimalTerritoryType>();
			}
			auto hex = Hex{ sectorDef.id(), index, terrainType, animalTerritoryType };
			hexes.push_back(hex);
		}

		sectorDef.set_hexes(hexes);
	}
}}