#include "map/hex.hxx"
#include <fmt/format.h>
#include <iostream>
#include <nlohmann/json.hpp>
#include <optional>

auto main(int argc, char* argv[]) -> int {
	using namespace std;
	using namespace Cryptid::Map;

	auto hex = Hex{ 1, TerrainType::Desert, StructureType::Menhir, StructureColor::Green, AnimalTerritoryType::Bear };
	cout << fmt::format("Hex: {}", hex) << endl;
	const json jHex = hex;
	cout << fmt::format("Hex from json: {}", jHex.dump(4)) << endl;
	return 0;
}
