#pragma once

#include "../lodash/lodash.hpp"
#include "hex.hpp"
#include <iostream>
#include <vector>

namespace Cryptid { namespace Map {
	class SectorDefinition {
	public:
		SectorDefinition() {}
		explicit SectorDefinition(int id, std::vector<Hex> hexes) : id_{ id }, hexes_{ std::move(hexes) } {}

		auto set_id(int val) noexcept -> void {
			id_ = val;
		}

		auto set_hexes(std::vector<Hex> val) noexcept -> void {
			hexes_ = std::move(val);
		}

		auto setInSlot(int slot, bool flipped) -> void {
			slot_ = slot;
			ld::each(hexes_, [slot, flipped](Hex& h) { h.setPosition(slot, flipped); });
		}

		auto setStructure(StructureType type, StructureColor color, int hexIndex) -> void {
			auto& hex = ld::find(hexes_, [hexIndex](const Hex& hex) { return hex.index() == hexIndex; });
			hex.setStructure(type, color);
		}

		auto initialized() const noexcept -> bool {
			return slot_ > -1 && ld::every(hexes_, [](const Hex& h) { return h.initialized(); });
		}

		auto id() const noexcept -> int {
			return id_;
		}

		auto slot() const noexcept -> int {
			return slot_;
		}

		auto hexes() const noexcept -> const std::vector<Hex>& {
			return hexes_;
		}

	private:
		int id_;
		int slot_ = -1;
		std::vector<Hex> hexes_;
	};

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
}}	 // namespace Cryptid::Map