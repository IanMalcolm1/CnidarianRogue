#pragma once

#include "Entities/EntityColiseum.h"
#include "Entities/ActorEntity.h"


class ActorFactory {
private:
   EntityColiseum<ActorEntity>* actorColiseum;

public:
   ActorFactory(EntityColiseum<ActorEntity>* actorColiseum)
      : actorColiseum(actorColiseum) {};


   ActorEntity* makePlayer();
   ActorEntity* makeEvilSmileyFace();
};
