#include "Entities/Damage.h"

std::string Damage::getDescription() {
   std::string desc = "Deals ";

   if (dice != 0) {
      desc.append( std::to_string(dice) + "d6+" );
   }

   desc.append( std::to_string(constant) );

   switch (type) {
   case DAMAGE_PHYSICAL:
      desc.append(" physical ");
      break;
   case DAMAGE_POISON:
      desc.append(" </green:poison\\> ");
      break;
   case DAMAGE_FROST:
      desc.append(" </lightblue:frost\\> ");
      break;
   case DAMAGE_FIRE:
      desc.append(" </red:fire\\> ");
      break;
   case DAMAGE_NONE:
      desc.append(" No Damage Type! ");
      break;
   }

   desc.append("damage");

   return desc;
}
