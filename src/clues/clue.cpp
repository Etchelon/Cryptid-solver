#include "clue.hpp"
#include <gsl/pointers>
#include <variant>

namespace Cryptid {
	using namespace Map;

	using nlohmann::json;

	auto from_json(const json& j, gsl::owner<Clue*>& clue) -> void {
		const auto negated = j.at("negated").get<bool>();
		const auto type = j.at("type").get<ClueType>();

		switch (type) {
		case ClueType::Landscape: {
			const auto terrainType1 = j.at("terrainType1").get<TerrainType>();
			const auto terrainType2 = j.at("terrainType2").get<TerrainType>();
			clue = new LandscapeClue{ terrainType1, terrainType2, negated };
			break;
		}

		case ClueType::Within1: {
			const auto terrainType = j.at("terrainType").get<TerrainType>();
			clue = new Within1Clue{ terrainType, negated };
			break;
		}

		case ClueType::Within2: {
			std::variant<StructureType, AnimalTerritoryType> structureOrAnimalTerritoryType;
			if (j.contains("structureType")) {
				j.at("structureType").get<StructureType>();
			} else {
				j.at("animalTerritory").get<AnimalTerritoryType>();
			}
			clue = new Within2Clue{ structureOrAnimalTerritoryType, negated };
			break;
		}

		case ClueType::Within3: {
			const auto color = j.at("color").get<StructureColor>();
			clue = new Within3Clue{ color, negated };
			break;
		}
		}
	}
}	// namespace Cryptid