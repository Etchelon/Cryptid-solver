#pragma once

#include "../map/hex.hpp"
#include "../map/shared.hpp"
#include <gsl/pointers>
#include <nlohmann/json.hpp>
#include <optional>
#include <variant>

namespace Cryptid {
	using namespace Map;

	enum class ClueType
	{
		Landscape,
		Within1,
		Within2,
		Within3
	};

	NLOHMANN_JSON_SERIALIZE_ENUM(ClueType, { { ClueType::Landscape, "Landscape" }, { ClueType::Within1, "Within1" },
											   { ClueType::Within2, "Within2" }, { ClueType::Within3, "Within3" } })

	class Clue {
	public:
		Clue(bool negated) : negated_{ negated } {}

		virtual auto distance() const noexcept -> int = 0;
		virtual auto isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool = 0;

	protected:
		bool negated_ = false;
	};

	class LandscapeClue final : public Clue {
	public:
		LandscapeClue() : Clue(false) {}
		explicit LandscapeClue(TerrainType terrainType1, TerrainType terrainType2, bool negated)
			: Clue(negated), terrainType1_{ terrainType1 }, terrainType2_{ terrainType2 } {}

		auto distance() const noexcept -> int override {
			return 0;
		}

		auto isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool override {
			throw 42;
		}

	private:
		TerrainType terrainType1_;
		TerrainType terrainType2_;
	};

	class Within1Clue final : public Clue {
	public:
		Within1Clue() : Clue(false) {}
		explicit Within1Clue(TerrainType terrainType, bool negated) : Clue(negated), terrainType_{ terrainType } {}

		auto distance() const noexcept -> int {
			return 1;
		}

		auto isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
			throw 42;
		}

	private:
		TerrainType terrainType_;
	};

	class Within2Clue final : public Clue {
	public:
		Within2Clue() : Clue(false) {}
		explicit Within2Clue(
			std::variant<StructureType, AnimalTerritoryType> structureOrAnimalTerritoryType, bool negated)
			: Clue(negated) {
			isStructure_ = std::holds_alternative<StructureType>(structureOrAnimalTerritoryType);
			if (isStructure_) {
				structureType_ = std::get<StructureType>(structureOrAnimalTerritoryType);
			} else {
				animalTerritoryType_ = std::get<AnimalTerritoryType>(structureOrAnimalTerritoryType);
			}
		}

		auto distance() const noexcept -> int {
			return 2;
		}

		auto isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
			throw 42;
		}

	private:
		bool isStructure_;
		std::optional<StructureType> structureType_;
		std::optional<AnimalTerritoryType> animalTerritoryType_;
	};

	class Within3Clue final : public Clue {
	public:
		Within3Clue() : Clue(false) {}
		explicit Within3Clue(StructureColor color, bool negated) : Clue(negated), color_{ color } {}

		auto distance() const noexcept -> int {
			return 3;
		}

		auto isHexOk(const Hex& hex, const std::vector<Hex>& nearbyHexes) const -> bool {
			throw 42;
		}

	private:
		StructureColor color_;
	};

	auto from_json(const nlohmann::json& j, gsl::owner<Clue*>& clue) -> void;
}	// namespace Cryptid