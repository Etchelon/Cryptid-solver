#include "clue.hpp"
#include "../lodash/lodash.hpp"
#include <gsl/pointers>
#include <variant>

namespace Cryptid {
	using namespace Map;

	auto LandscapeClue::isHexOk(const Hex& hex, const std::vector<Hex>& allHexes) const -> bool {
		const auto hexType = hex.terrainType();
		return hexType == terrainType1_ || hexType == terrainType2_;
	}

	auto Within1Clue::isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
		return hex.terrainType() == terrainType_ || ld::any(nearbyHexes, [terrainType = terrainType_](const Hex& h) {
			return h.terrainType() == terrainType;
		});
	}

	auto Within2Clue::isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
		if (isStructure_) {
			const auto predicate = [structureType = structureType_.value()](const Hex& h) {
				return h.hasStructure() && h.structure().type == structureType;
			};
			return predicate(hex) || ld::any(nearbyHexes, predicate);
		}

		const auto predicate = [animalTerritoryType = animalTerritoryType_.value()](const Hex& h) {
			return h.hasAnimalTerritory() && h.animalTerritoryType() == animalTerritoryType;
		};
		return predicate(hex) || ld::any(nearbyHexes, predicate);
	}

	auto Within3Clue::isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
		const auto predicate = [color = color_](
								   const Hex& h) { return h.hasStructure() && h.structure().color == color; };
		return predicate(hex) || ld::any(nearbyHexes, predicate);
	}

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
				structureOrAnimalTerritoryType = j.at("structureType").get<StructureType>();
			} else {
				structureOrAnimalTerritoryType = j.at("animalTerritory").get<AnimalTerritoryType>();
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