#pragma once

#include "shared.hpp"
#include <exception>
#include <fmt/core.h>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>
#include <string_view>
#include <tuple>

namespace Cryptid { namespace Map {
	auto calculateRow(int sectorSlot, int hexIndex) -> int;
	auto calculateColumn(int sectorSlot, int hexIndex) -> int;

	class Hex {
	public:
		Hex() {}
		explicit Hex(int sectorId, int index, TerrainType terrainType,
			std::optional<AnimalTerritoryType> animalTerritoryType = std::nullopt)
			: sectorId_{ sectorId }, index_{ index }, terrainType_{ terrainType }, animalTerritoryType_{
				  animalTerritoryType
			  } {
			id_ = fmt::format("{}-{}", sectorId, index);
		}

		// Setters

		auto setStructure(StructureType type, StructureColor color) -> void {
			structure_ = { color, type };
		}

		auto setPosition(int sectorSlot, bool sectorFlipped) -> void {
			auto index = sectorFlipped ? N_HEXES_PER_SECTOR - 1 - index_ : index_;
			row_ = calculateRow(sectorSlot, index);
			column_ = calculateColumn(sectorSlot, index);
			initialized_ = true;
		}

		// Getters

		auto id() const noexcept -> const std::string& {
			return id_;
		}

		auto initialized() const noexcept -> bool {
			return initialized_;
		}

		auto row() const noexcept -> int {
			return row_;
		}

		auto column() const noexcept -> int {
			return column_;
		}

		auto terrainType() const noexcept -> TerrainType {
			return terrainType_;
		}

		auto hasStructure() const noexcept -> bool {
			return structure_.has_value();
		}

		auto structure() const -> const Structure& {
			if (!hasStructure()) {
				auto message = fmt::format("Hex {} in sector {} has no structure", index_, sectorId_);
				throw std::runtime_error{ message };
			}
			return structure_.value();
		}

		auto hasAnimalTerritory() const noexcept -> bool {
			return animalTerritoryType_.has_value();
		}

		auto animalTerritoryType() const -> AnimalTerritoryType {
			if (!hasAnimalTerritory()) {
				auto message = fmt::format("Hex {} in sector {} has no animal territory", index_, sectorId_);
				throw std::runtime_error{ message };
			}
			return animalTerritoryType_.value();
		}

	private:
		bool initialized_ = false;
		std::string id_;
		int sectorId_;
		int sectorSlot_;
		int index_;
		int row_;
		int column_;
		TerrainType terrainType_;
		std::optional<AnimalTerritoryType> animalTerritoryType_;
		std::optional<Structure> structure_ = std::nullopt;
	};
}}	 // namespace Cryptid::Map

using namespace Cryptid::Map;
