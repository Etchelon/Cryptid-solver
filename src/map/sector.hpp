#pragma once

#include "../lodash/lodash.hpp"
#include "hex.hpp"
#include <iostream>
#include <vector>

namespace Cryptid { namespace Map {
	class SectorDefinition {
	public:
		SectorDefinition() {}
		explicit SectorDefinition(int id, std::vector<Hex> hexes) : id_{ id }, hexes_{ std::move(hexes) } {}

		auto set_id(int val) noexcept -> void {
			id_ = val;
		}

		auto set_hexes(std::vector<Hex> val) noexcept -> void {
			hexes_ = std::move(val);
		}

		auto setInSlot(int slot, bool flipped) -> void {
			slot_ = slot;
			ld::each(hexes_, [=](Hex& h) { h.setPosition(slot, flipped); });
		}

		auto setStructure(StructureType type, StructureColor color, int hexIndex) -> void {
			auto& hex = ld::first(hexes_, [hexIndex](const Hex& hex) { return hex.index() == hexIndex; });
			hex.setStructure(type, color);
		}

		auto initialized() const noexcept -> bool {
			return slot_ > -1 && ld::every(hexes_, [](const Hex& h) { return h.initialized(); });
		}

		auto id() const noexcept -> int {
			return id_;
		}

		auto slot() const noexcept -> int {
			return slot_;
		}

		auto hexes() const noexcept -> const std::vector<Hex>& {
			return hexes_;
		}

	private:
		int id_;
		int slot_ = -1;
		std::vector<Hex> hexes_;
	};

	using nlohmann::json;

	auto from_json(const json& j, SectorDefinition& sectorDef) -> void;
}}	 // namespace Cryptid::Map