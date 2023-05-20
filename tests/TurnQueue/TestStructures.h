#pragma once

#include <string>


struct ActorEntity {
   int id;

   ActorEntity(int id) : id(id) {};
};


struct Effect {
   char id;

   Effect(char id = '*') : id(id) {};

   bool operator == (const Effect effect) {
      return (id==effect.id);
   }
};
