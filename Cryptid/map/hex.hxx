#pragma once

#include "shared.hxx"
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string_view>

namespace Cryptid { namespace Map {
	class Hex {
	public:
		Hex() {}
		Hex(int sector, TerrainType terrainType, std::optional<StructureType> structureType = std::nullopt,
			std::optional<StructureColor> structureColor = std::nullopt, std::optional<AnimalTerritoryType> animalTerritoryType = std::nullopt)
			: sector_{ sector }, terrainType_{ terrainType }, animalTerritoryType_{ animalTerritoryType } {
			if (structureType.has_value()) {
				structure_ = { structureColor.value(), structureType.value() };
			}
		}

	public:
		int sector_;
		int index_;
		int row_;
		int column_;
		TerrainType terrainType_;
		std::optional<Structure> structure_;
		std::optional<AnimalTerritoryType> animalTerritoryType_;
	};

	using nlohmann::json;

	auto to_json(json& j, const Hex& hex) -> void {
		j = json{ { "sector", hex.sector_ }, { "terrainType", hex.terrainType_ } };
		if (hex.structure_.has_value()) {
			const auto& structure = hex.structure_.value();
			j.push_back({ "structureType", structure.type });
			j.push_back({ "structureColor", structure.color });
		}
		if (hex.animalTerritoryType_.has_value()) {
			j.push_back({ "animalTerritoryType", hex.animalTerritoryType_.value() });
		}
	}

	auto from_json(const json& j, Hex& hex) -> void {
		j.at("sector").get_to(hex.sector_);
		j.at("terrainType").get_to(hex.terrainType_);
		if (j.contains("structureType")) {
			auto structureType = j.at("structureType").get<StructureType>();
			auto structureColor = j.at("structureColor").get<StructureColor>();
			hex.structure_ = Structure{ structureColor, structureType };
		}
		if (j.contains("animalTerritoryType")) {
			hex.animalTerritoryType_ = j.at("animalTerritoryType").get<AnimalTerritoryType>();
		}
	}
}}	 // namespace Cryptid::Map

using namespace Cryptid::Map;

template<>
struct fmt::formatter<Hex> : fmt::formatter<std::string_view> {
	template<typename FormatContext>
	auto format(const Hex& hex, FormatContext& ctx) const {
		auto type = toString(hex.terrainType_);
		return format_to(ctx.out(), "Terrain: {}", type);
	}
};
