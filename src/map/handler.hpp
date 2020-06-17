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

		auto findHexesWithin(const Hex& hex, int distance) const -> std::vector<ld::Ref<Hex>>;
		auto findHexesWithin1(int row, int column) const -> std::vector<ld::Ref<Hex>>;
		auto getHexAt(int row, int column) const -> ld::NullableRef<Hex>;

	private:
		std::vector<Hex> hexes_;
	};
}}	 // namespace Cryptid::Map