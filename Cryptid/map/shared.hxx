#pragma once

#include <string>

namespace Cryptid { namespace Map {
	enum class TerrainType
	{
		Desert,
		Forest,
		Mountain,
		Lake,
		Swamp
	};

	auto toString(TerrainType type) -> std::string {
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

	auto toString(StructureColor color) -> std::string {
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
		AbandonedTent,
		Menhir
	};

	auto toString(StructureType type) -> std::string {
		switch (type) {
		case StructureType::AbandonedTent:
			return "Abandoned Tent";
		case StructureType::Menhir:
			return "Menhir";
		}
	}

	enum class AnimalTerritoryType
	{
		Bear,
		Puma
	};

	auto toString(AnimalTerritoryType type) -> std::string {
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