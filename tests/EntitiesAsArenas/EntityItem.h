#include "Entity.h"


class EntityItem : public Entity {
private:

public:
   TileDisplay display;
   Description description;


   EntityItem(int id, int bytesUsed, int totalSpace) : Entity(id, bytesUsed, totalSpace),
      display(TileDisplay()) {
      description = Description(); };
};
