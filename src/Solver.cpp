#include "Solver.hpp"

namespace Cryptid {
	auto Solver::solve() const -> ld::NullableRef<Hex> {
		return ld::firstOrDefault(mapHandler_.hexes(), [this](const Hex& hex) {
			return ld::every(clues_, [&hex, this](const gsl::owner<Clue*>& clue) { return isHexOk(hex, clue); });
		});
	}

	auto Solver::isHexOk(const Hex& hex, gsl::owner<Clue*> clue) const -> bool {
		const auto nearbyHexes = mapHandler_.findHexesWithin(hex, clue->distance());
		const auto hexesToCheck = ld::map<Hex>(nearbyHexes, [](const ld::Ref<Hex>& hRef) { return hRef.get(); });
		return clue->isHexOk(hex, hexesToCheck);
	}
}	// namespace Cryptid