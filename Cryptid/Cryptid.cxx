#include "map/sector.hxx"
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

	auto sectorDefPath = fs::current_path() / "map" / "sectors.json";
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

	auto mapStateFilePath = fs::current_path() / "map" / "state.json";
	auto mapStateStr = readFile(mapStateFilePath);

	return 0;
}
