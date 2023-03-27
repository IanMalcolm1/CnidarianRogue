#pragma once

#include <string>

enum ActorType {
   ACTOR_TYPE_HUMANOID
};

struct ActorData {
   int id;
};

struct HumanoidActorData : ActorData {
   std::string name;
};

struct Actor {
   ActorType type;
   int id;
   ActorData* data;
};
