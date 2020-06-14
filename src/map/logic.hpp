#pragma once

#include "../lodash/lodash.hpp"
#include "hex.hpp"
#include <exception>
#include <memory>
#include <optional>
#include <vector>

namespace Cryptid { namespace Map {
	class MapHandler {
	public:
		MapHandler() {}

		auto set_hexes(std::vector<Hex> hexes) -> void {
			hexes_ = std::move(hexes);
		}

		auto hexes() const noexcept -> const std::vector<Hex>& {
			return hexes_;
		}

		auto findHexesWithin(const Hex& hex, int distance) -> std::vector<ld::Ref<Hex>> {
			auto hexes = std::vector<ld::Ref<Hex>>{};
			if (distance == 0) {
				return hexes;
			}

			auto hexesWithin1 = findHexesWithin1(hex.row(), hex.column());
			if (distance == 1) {
				return hexesWithin1;
			}

			for (const auto& h : hexesWithin1) {
				hexes.push_back(h);
				auto hexesWithinR = findHexesWithin(h, (distance - 1));
			}
			return hexes;
		}

		auto findHexesWithin1(int row, int column) -> std::vector<ld::Ref<Hex>> {
			auto surroundingHexes = std::vector<ld::NullableRef<Hex>>{
				getHexAt((row - 2), column),
				getHexAt((row + 2), column),
				getHexAt((row - 1), (column - 1)),
				getHexAt((row + 1), (column - 1)),
				getHexAt((row - 1), (column + 1)),
				getHexAt((row + 1), (column + 1)),
			};

			std::erase_if(surroundingHexes, [](const ld::NullableRef<Hex>& h) { return !h.has_value(); });
			return ld::map<ld::Ref<Hex>>(
				surroundingHexes, [](const ld::NullableRef<Hex>& h) -> ld::Ref<Hex> { return h.value(); });
		}

		auto getHexAt(int row, int column) -> ld::NullableRef<Hex> {
			return ld::firstOrDefault(
				hexes_, [row, column](const Hex& hex) { return hex.row() == row && hex.column() == column; });
		}

	private:
		std::vector<Hex> hexes_;
	};
}}	 // namespace Cryptid::Map