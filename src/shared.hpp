#pragma once

#include <nlohmann/json.hpp>
#include <string>

namespace Cryptid {
	constexpr int N_SECTORS = 6;
	constexpr int N_HEXES_PER_SECTOR = 18;

	template<typename T>
	inline auto parseEnum(const std::string& type) -> T {
		throw std::runtime_error{ "Not implemented." };
	}

	enum class TerrainType
	{
		Desert,
		Forest,
		Mountain,
		Lake,
		Swamp,
		Animal
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(TerrainType,
		{ { TerrainType::Desert, "Desert" }, { TerrainType::Forest, "Forest" }, { TerrainType::Mountain, "Mountain" },
			{ TerrainType::Lake, "Lake" }, { TerrainType::Swamp, "Swamp" }, { TerrainType::Animal, "Animal" } })

	inline auto toString(TerrainType type) -> std::string {
		switch (type) {
		case TerrainType::Desert:
			return "Desert";
		case TerrainType::Forest:
			return "Forest";
		case TerrainType::Mountain:
			return "Mountain";
		case TerrainType::Lake:
			return "Lake";
		case TerrainType::Swamp:
			return "Swamp";
		}
	}

	enum class StructureColor
	{
		Black,
		Blue,
		Green,
		White
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(
		StructureColor, { { StructureColor::Black, "Black" }, { StructureColor::Blue, "Blue" },
							{ StructureColor::Green, "Green" }, { StructureColor::White, "White" } })

	inline auto toString(StructureColor color) -> std::string {
		switch (color) {
		case StructureColor::Black:
			return "Black";
		case StructureColor::Blue:
			return "Blue";
		case StructureColor::Green:
			return "Green";
		case StructureColor::White:
			return "White";
		}
	}

	enum class StructureType
	{
		AbandonedShack,
		StandingStone
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(StructureType,
		{ { StructureType::AbandonedShack, "AbandonedShack" }, { StructureType::StandingStone, "StandingStone" } })

	inline auto toString(StructureType type) -> std::string {
		switch (type) {
		case StructureType::AbandonedShack:
			return "Abandoned Shack";
		case StructureType::StandingStone:
			return "Standing Stone";
		}
	}

	enum class AnimalTerritoryType
	{
		Bear,
		Puma
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(
		AnimalTerritoryType, { { AnimalTerritoryType::Bear, "Bear" }, { AnimalTerritoryType::Puma, "Puma" } })

	inline auto toString(AnimalTerritoryType type) -> std::string {
		switch (type) {
		case AnimalTerritoryType::Bear:
			return "Bear";
		case AnimalTerritoryType::Puma:
			return "Puma";
		}
	}

	struct Structure {
		StructureColor color;
		StructureType type;
	};
}	// namespace Cryptid