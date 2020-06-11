#pragma once

#include <string>

namespace Cryptid { namespace Map {
	constexpr int N_HEXES_PER_SECTOR = 18;

	enum class TerrainType
	{
		Desert,
		Forest,
		Mountain,
		Lake,
		Swamp
	};

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
}}	 // namespace Cryptid::Map