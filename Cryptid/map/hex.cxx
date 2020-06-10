#include "hex.hxx"
#include <tuple>
#include <unordered_map>

namespace Cryptid { namespace Map {
	constexpr int hexesPerRow = 6;
	static std::unordered_map<int, std::tuple<int, int>> sectorOffsets = { { 0, std::make_tuple(0, 0) },
		{ 1, std::make_tuple(0, 6) }, { 2, std::make_tuple(6, 0) }, { 3, std::make_tuple(6, 6) },
		{ 2, std::make_tuple(12, 0) }, { 3, std::make_tuple(12, 6) } };

	auto calculateRow(int sectorSlot, int hexIndex) -> int {
		const auto& offset = sectorOffsets.at(sectorSlot);
		const auto& [rowOffset, columnOffset] = offset;
		int row = hexIndex / hexesPerRow;
		int oddOffset = hexIndex % 2;
		return row + oddOffset + rowOffset;
	}

	auto calculateColumn(int sectorSlot, int hexIndex) -> int {
		const auto& offset = sectorOffsets.at(sectorSlot);
		const auto& [rowOffset, columnOffset] = offset;
		int column = hexIndex % hexesPerRow;
		return column + columnOffset;
	}
}}	 // namespace Cryptid::Map