#pragma once

#include "Topography/TileCoordinates.h"


enum PathingType {
   PATH_LINE,
   PATH_ROUTE,
};

enum TraversibilityType {
   TRAV_IGNORE_NONE,
   TRAV_INCLUDE_UNSEEN_TILES,
   TRAV_IGNORE_ACTORS,
};

struct LinePathInfo {
   int penetration;
};

struct PathingSpecs {
   PathingType type;
   TileCoords start, end;
   TraversibilityType traversibility;

   union {
      LinePathInfo lineInfo;
   };

   PathingSpecs(PathingType type = PATH_ROUTE, TraversibilityType traversibility = TRAV_IGNORE_NONE) :
   type(type), traversibility(traversibility) {};
};
