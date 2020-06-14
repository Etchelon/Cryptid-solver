#include "hex.hpp"
#include <iostream>
#include <tuple>
#include <unordered_map>

namespace Cryptid { namespace Map {
	constexpr int hexesPerRow = 6;
	static std::unordered_map<int, std::tuple<int, int>> sectorOffsets = { { 0, std::make_tuple(0, 0) },
		{ 1, std::make_tuple(0, 6) }, { 2, std::make_tuple(6, 0) }, { 3, std::make_tuple(6, 6) },
		{ 4, std::make_tuple(12, 0) }, { 5, std::make_tuple(12, 6) } };

	auto calculateRow(int sectorSlot, int hexIndex) -> int {
		const auto& sectorOffset = sectorOffsets.at(sectorSlot);
		const auto& [rowOffset, columnOffset] = sectorOffset;
		int row = 2 * (hexIndex / hexesPerRow);
		int oddOffset = hexIndex % 2;
		return row + oddOffset + rowOffset;
	}

	auto calculateColumn(int sectorSlot, int hexIndex) -> int {
		const auto& offset = sectorOffsets.at(sectorSlot);
		const auto& [rowOffset, columnOffset] = offset;
		int column = hexIndex % hexesPerRow;
		return column + columnOffset;
	}

	auto operator<<(std::ostream& out, const Hex& hex) -> std::ostream& {
		out << fmt::format("Hex {}, terrain: {} - coordinates: ({}, {}){}{}\n", hex.id(), toString(hex.terrainType()),
			hex.row(), hex.column(),
			hex.hasAnimalTerritory() ? fmt::format(", home to some {}s", toString(hex.animalTerritoryType())) : "",
			hex.hasStructure()
				? fmt::format(", houses a {} {}", toString(hex.structure().color), toString(hex.structure().type))
				: "");
		return out;
	}
}}	 // namespace Cryptid::Map