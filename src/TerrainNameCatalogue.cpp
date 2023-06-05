#include "Topography/TerrainNameCatalogue.h"


int TerrainNameCatalogue::addName(std::string name) {
   int index = names.size();
   names.push_back(name);
   return index;
}

std::string TerrainNameCatalogue::getName(int index) {
   return names[index];
}
