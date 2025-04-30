#ifndef MAPSYSTEM_H
#define MAPSYSTEM_H

#include "hero.h"
#include <raylib.h>

typedef struct Map {
  Texture2D texture;
}Map;

Map* MapInit(Texture2D texture);
void DrawMap(Map* map, Hero* hero);
void MapDestroy(Map* map);

// void map_is_island(Hero* hero);
// void map_is_grassland(Hero* hero);
// void map_is_volcano(Hero* hero);
// void map_cleanup_islandmap();
// void map_cleanup_grassland();
// void map_cleanup_volcano();

#endif
  
