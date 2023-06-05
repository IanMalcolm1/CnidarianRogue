#pragma once

#include <string>
#include <vector>


class TerrainNameCatalogue {
private:
   std::vector<std::string> names;

public:
   //returns id assigned to the passed name
   int addName(std::string name);
   std::string getName(int index);
};
