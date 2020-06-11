#include "map/sector.hpp"
#include <algorithm>
#include <exception>
#include <filesystem>
#include <fmt/core.h>
#include <fstream>
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
	using namespace Cryptid::Map;
	namespace fs = std::filesystem;

	auto sectorDefPath = fs::current_path() / "src" / "map" / "sectors.json";
	auto sectorsStr = readFile(sectorDefPath);

	using nlohmann::json;
	auto jSectors = json::parse(sectorsStr);
	std::vector<SectorDefinition> sectorDefs;
	for (const auto& jSector : jSectors.items()) {
		auto sectorDef = jSector.value().get<SectorDefinition>();
		sectorDefs.push_back(sectorDef);
	}

	std::cout << sectorDefs.size() << " elements parsed\n";

	int nInitialized = std::count_if(
		sectorDefs.cbegin(), sectorDefs.cend(), [](const SectorDefinition& sec) { return sec.initialized(); });
	std::cout << nInitialized << " elements initialized\n";

	auto mapStateFilePath = fs::current_path() / "src" / "state.json";
	auto mapStateStr = readFile(mapStateFilePath);
	auto mapState = json::parse(mapStateStr);

	auto sectorsState = mapState.at("sectors").items();
	for (const auto& [key, value] : sectorsState) {
		auto sectorId = value.at("id").get<int>();
		auto slot = value.at("slot").get<int>();
		auto flipped = value.at("flipped").get<bool>();

		auto sectorIt = std::find_if(sectorDefs.begin(), sectorDefs.end(),
			[sectorId](const SectorDefinition& sec) { return sec.id_ == sectorId; });
		if (sectorIt == sectorDefs.end()) {
			throw std::runtime_error{ fmt::format("Sector with id {} not found among definitions", sectorId) };
		}

		auto& sectorDef = *sectorIt;
		std::for_each(sectorDef.hexes_.begin(), sectorDef.hexes_.end(),
			[slot, flipped](Hex& h) { h.setPosition(slot, flipped); });
	}

	auto structures = mapState.at

						  nInitialized = std::count_if(
		sectorDefs.cbegin(), sectorDefs.cend(), [](const SectorDefinition& sec) { return sec.initialized(); });
	std::cout << nInitialized << " elements initialized\n";

	return 0;
}
