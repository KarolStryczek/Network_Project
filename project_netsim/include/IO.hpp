// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 05.01.2019.
//

#ifndef PROJECT_NETSIM_IO_HPP
#define PROJECT_NETSIM_IO_HPP

#include "Factory_Package/Factory.hpp"
#include "DataTypes.hpp"
#include "Storage/IPackageQueue.hpp"
#include "Storage/PackageQueue.hpp"
#include "Nodes/Ramp.hpp"
#include "Nodes/Worker.hpp"
#include "Nodes/Storehouse.hpp"

#include <istream>
#include <ostream>
#include <utility>
#include <map>
#include <vector>
#include <memory>

using markers_t = std::vector<std::pair<std::string, std::map<std::string, std::string>>>;

enum class ElementsOfNetwork {
    Ramp, Worker, Storehouse
};

bool loadFactoryStructure(std::istream &input, Factory &factory);
bool loadFactoryStructureFromFile(std::string filename, Factory &factory);
void saveFactoryStructure(std::ostream &output, const Factory &factory);
bool saveFactoryStructureToFile(std::string filename, const Factory &factory);
markers_t syntaxAnalysis(std::vector<std::string> lines_vector);
void semanticCorrectness(markers_t initial_data, Factory &factory);

#endif //PROJECT_NETSIM_IO_HPP
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
