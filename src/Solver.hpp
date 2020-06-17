#pragma once

#include "clues/clue.hpp"
#include "lodash/lodash.hpp"
#include "map/handler.hpp"
#include <gsl/pointers>
#include <vector>

namespace Cryptid {
	class Solver {
	public:
		explicit Solver(Map::MapHandler mapHandler, std::vector<gsl::owner<Clue*>> clues)
			: mapHandler_{ std::move(mapHandler) }, clues_{ std::move(clues) } {}

		auto solve() const -> ld::NullableRef<Hex>;

	private:
		auto isHexOk(const Hex& hex, gsl::owner<Clue*> clue) const -> bool;

	private:
		Map::MapHandler mapHandler_;
		std::vector<gsl::owner<Clue*>> clues_;
	};
}	// namespace Cryptid