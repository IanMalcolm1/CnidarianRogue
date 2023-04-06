#include "Entities/Entity.h"


class ItemEntity : public Entity {
private:

public:
   TileDisplay display;
   Description description;


   ItemEntity(int id, int bytesUsed, int totalSpace) : Entity(id, bytesUsed, totalSpace),
      display(TileDisplay()) {
      description = Description(); };
};
