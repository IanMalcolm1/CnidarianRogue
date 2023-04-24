#include "Adventure/Adventure.h"

void Adventure::linkPlayerAndScene() {
   playerMan.setSceneDependencies(scene.getTurnQueue(), scene.getMap(), &confirmer);
}


void Adventure::changeScene() {
   scene.~Scene();
   scene = Scene(&log, &playerMan); //appears to be because of LocalMap
   linkPlayerAndScene();
}
