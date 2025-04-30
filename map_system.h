#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include "hero.h"

void map_is_island(Hero* hero);
void map_is_grassland(Hero* hero);
void map_is_volcano(Hero* hero);
void map_cleanup_islandmap();
void map_cleanup_grassland();
void map_cleanup_volcano();

#endif
