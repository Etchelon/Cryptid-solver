#pragma once

#include "hex.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace Cryptid { namespace Map {
	constexpr int N_HEXES_PER_SECTOR = 18;

	class SectorDefinition {
	public:
		SectorDefinition() {}
		explicit SectorDefinition(int id, std::vector<Hex> hexes) : id_{ id }, hexes_{ std::move(hexes) } {}

		auto initialized() const noexcept -> bool {
			return std::all_of(hexes_.cbegin(), hexes_.cend(), [](const Hex& h) { return h.initialized(); });
		}

	public:
		int id_;
		std::vector<Hex> hexes_ = std::vector<Hex>{ N_HEXES_PER_SECTOR };
	};

	using nlohmann::json;

	auto from_json(const json& j, SectorDefinition& sectorDef) -> void {
		j.at("id").get_to(sectorDef.id_);
		auto jHexes = j.at("hexes");
		std::vector<Hex> hexes{ N_HEXES_PER_SECTOR };
		for (const auto& [key, jHex] : jHexes.items()) {
			int index = std::stoi(key);
			auto terrainType = jHex.at("terrainType").get<TerrainType>();
			std::optional<AnimalTerritoryType> animalTerritoryType = std::nullopt;
			if (jHex.contains("animalTerritoryType")) {
				animalTerritoryType = jHex.at("animalTerritoryType").get<AnimalTerritoryType>();
			}
			auto hex = Hex{ sectorDef.id_, index, terrainType, animalTerritoryType };
		}
	}
}}	 // namespace Cryptid::Map