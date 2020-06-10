#pragma once

#include "hex.hxx"
#include <vector>

namespace Cryptid { namespace Map {
	constexpr int N_HEXES_PER_SECTOR = 18;

	class SectorDefinition {
	public:
		SectorDefinition(int id, std::vector<Hex> hexes) : id_{ id }, hexes_{ std::move(hexes) } {}

	public:
		int id_;
		std::vector<Hex> hexes_ = std::vector<Hex>{ N_HEXES_PER_SECTOR };
	};
}}	 // namespace Cryptid::Map