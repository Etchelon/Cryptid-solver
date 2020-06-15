#include "clues/clue.hpp"
#include "map/logic.hpp"
#include "map/sector.hpp"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
#include <gsl/pointers>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

auto readFile(const std::filesystem::path& path) -> std::string {
	std::ifstream ifs{ path };
	if (!ifs) {
		throw std::filesystem::filesystem_error{
			fmt::format("Could not open the sectors definition file {}", path.string()), std::error_code{}
		};
	}

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	return buffer.str();
}

auto main(int argc, char* argv[]) -> int {
	using namespace Cryptid;
	using namespace Cryptid::Map;
	namespace fs = std::filesystem;

	auto sectorDefPath = fs::current_path() / "src" / "map" / "sectors.json";
	auto sectorsStr = readFile(sectorDefPath);

	using nlohmann::json;
	auto jSectors = json::parse(sectorsStr);
	auto sectors = std::vector<SectorDefinition>{};
	sectors.reserve(N_SECTORS);
	for (const auto& jSector : jSectors.items()) {
		auto sectorDef = jSector.value().get<SectorDefinition>();
		sectors.push_back(sectorDef);
	}

	std::cout << sectors.size() << " elements parsed\n";

	int nInitialized =
		std::count_if(sectors.cbegin(), sectors.cend(), [](const SectorDefinition& sec) { return sec.initialized(); });
	std::cout << nInitialized << " elements initialized\n";

	auto mapStateFilePath = fs::current_path() / "src" / "state.json";
	auto mapStateStr = readFile(mapStateFilePath);
	auto mapState = json::parse(mapStateStr);

	auto sectorStates = mapState.at("sectors").items();
	for (const auto& [key, value] : sectorStates) {
		auto sectorId = value.at("id").get<int>();
		auto slot = value.at("slot").get<int>();
		auto flipped = value.at("flipped").get<bool>();

		auto& sectorDef = ld::first(sectors, [sectorId](const SectorDefinition& sec) { return sec.id() == sectorId; });
		sectorDef.setInSlot(slot, flipped);
	}

	auto structures = mapState.at("structures").items();
	for (const auto& [key, value] : structures) {
		auto slot = value.at("slot").get<int>();
		auto type = value.at("type").get<StructureType>();
		auto color = value.at("color").get<StructureColor>();
		auto hex = value.at("hex").get<int>();

		auto& sector = ld::first(sectors, [slot](const SectorDefinition& sec) { return sec.slot() == slot; });
		sector.setStructure(type, color, hex);
	}

	nInitialized =
		std::count_if(sectors.cbegin(), sectors.cend(), [](const SectorDefinition& sec) { return sec.initialized(); });
	std::cout << nInitialized << " elements initialized\n";

	std::vector<Hex> allHexes;
	allHexes.reserve(N_SECTORS * N_HEXES_PER_SECTOR);
	ld::each(sectors, [&allHexes](const SectorDefinition& sec) {
		ld::each(sec.hexes(), [&allHexes](const Hex& hex) { allHexes.push_back(hex); });
	});

	ld::each(allHexes, [](const Hex& hex) { std::cout << hex << "\n"; });

	auto mapHandler = MapHandler{};
	mapHandler.set_hexes(allHexes);
	auto h = mapHandler.getHexAt(0, 0);
	if (h.has_value()) {
		auto& hex = ld::get(h);
		auto within1 = mapHandler.findHexesWithin(hex, 1);
		std::cout << "Hexes within 1 of " << hex << ": \n";
		ld::each(within1, [](const auto hexRef) { std::cout << hexRef.get() << "\n"; });
	}

	auto players = mapState.at("players").items();
	auto clues = std::vector<gsl::owner<Clue*>>{};
	for (const auto& [key, value] : players) {
		auto clue = value.at("clue").get<gsl::owner<Clue*>>();
		clues.push_back(clue);
	}

	return 0;
}
