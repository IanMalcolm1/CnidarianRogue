#include "Algorithms/PathingSpecs.h"
#include <climits>

PathingSpecs::PathingSpecs(PathingType type, TraversibilityType traversibility) : type(type), traversibility(traversibility) {
   switch (type) {
      case PATH_ROUTE:
         routeInfo.maxAStarTiles = INT_MAX;
         break;
      case PATH_LINE:
         lineInfo.range = INT_MAX;
         break;
   }
};

