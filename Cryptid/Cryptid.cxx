#include "map/sector.hxx"
#include <filesystem>
#include <fmt/format.h>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <sstream>

auto main(int argc, char* argv[]) -> int {
	using namespace Cryptid::Map;
	namespace fs = std::filesystem;

	const auto sectorDefPath = fs::current_path() / "map" / "sectors.json";
	std::ifstream ifs{ sectorDefPath };
	if (!ifs) {
		std::cerr << "Could not open the sectors definition file " << sectorDefPath << "\n";
		return 1;
	}

	std::stringstream buffer;
	buffer << ifs.rdbuf();
	auto sectorsStr = buffer.str();

	using nlohmann::json;
	auto jSectors = json::parse(sectorsStr);
	std::vector<SectorDefinition> sectorDefs;
	sectorDefs.reserve(jSectors.size());
	for (const auto& jSector : jSectors.items()) {
		const auto& val = jSector.value();
		auto sectorId = val.at("id").get<int>();
		std::cout << sectorId << "\n\n" << jSector.value().dump(4) << "\n\n\n";
		auto sectorDef = jSector.value().get<SectorDefinition>();
		sectorDefs.push_back(sectorDef);
	}

	std::cout << sectorDefs.size() << " elements parsed"
			  << "\n";

	return 0;
}
