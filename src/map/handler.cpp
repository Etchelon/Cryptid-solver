#include "handler.hpp"

namespace Cryptid { namespace Map {
	auto MapHandler::findHexesWithin(const Hex& hex, int distance) const -> std::vector<ld::Ref<Hex>> {
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
			ld::each(hexesWithinR, [&hexes](const ld::Ref<Hex>& hRef) {
				const auto alreadyInVector =
					ld::any(hexes, [&hRef](const ld::Ref<Hex>& hh) { return hRef.get().id() == hh.get().id(); });
				if (alreadyInVector) {
					return;
				}
				hexes.push_back(hRef);
			});
		}
		return hexes;
	}

	auto MapHandler::findHexesWithin1(int row, int column) const -> std::vector<ld::Ref<Hex>> {
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

	auto MapHandler::getHexAt(int row, int column) const -> ld::NullableRef<Hex> {
		return ld::firstOrDefault(
			hexes_, [row, column](const Hex& hex) { return hex.row() == row && hex.column() == column; });
	}
}}	 // namespace Cryptid::Map