#include "Entity.h"
#include "../ExampleEntities/TestComponents.h"


class EntityItem : public Entity {
private:
   TileDisplay display;
   DescribableComp description;

public:
   EntityItem(int bytesUsed, int totalSpace) : Entity(bytesUsed, totalSpace),
      display(TileDisplay()), description(DescribableComp()) {};
   
   Component* getComponent(ComponentType type);
   void removeComponent(ComponentType type);
};
