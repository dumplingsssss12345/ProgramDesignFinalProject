#include <stdlib.h>
#include "raylib.h"
#include "map_system.h"
#include "hero.h"


// static Texture2D islandmap = {0};
// static Texture2D grassland = {0};
// static Texture2D volcano = {0};
// static bool islandLoaded = false;
// static bool grasslandLoaded = false;
// static bool volcanoLoaded = false;
static const int textureSize = 1024;

Map* MapInit(Texture2D texture) {
    Map* map = (Map*)malloc(sizeof(Map));

    map->texture = texture;

    return map;
}

void DrawMap(Map* map, Hero* hero) {
    int centerX = (int)(hero->position.x / textureSize);
    int centerY = (int)(hero->position.y / textureSize);

    // 畫4*4個格子圍繞玩家
    for (int i = -2; i <= 1; i++) {
        for (int j = -2; j <= 1; j++) {
            int drawX = (centerX + i) * textureSize;
            int drawY = (centerY + j) * textureSize;
            DrawTexture(map->texture, drawX, drawY, WHITE);
        }
    }
}

void MapDestroy(Map* map) {
    UnloadTexture(map->texture);
    free(map);
}

// void map_is_island(Hero* hero) {
//     //加載紋理1次
//     if (!islandLoaded) {
//         islandmap = LoadTexture("resources/map/island.png");
//         islandLoaded = true;
//     }

    

//     int centerX = (int)(hero->position.x / textureSize);
//     int centerY = (int)(hero->position.y / textureSize);

//     // 畫4*4個格子圍繞玩家
//     for (int i = -2; i <= 1; i++) {
//         for (int j = -2; j <= 1; j++) {
//             int drawX = (centerX + i) * textureSize;
//             int drawY = (centerY + j) * textureSize;
//             DrawTexture(islandmap, drawX, drawY, WHITE);
//         }
//     }
// }

// void map_is_grassland(Hero* hero) {
//     //加載紋理1次
//     if (!grasslandLoaded) {
//         grassland = LoadTexture("resources/map/grassland.png");
//         grasslandLoaded = true;
//     }

//     int centerX = (int)(hero->position.x / textureSize);
//     int centerY = (int)(hero->position.y / textureSize);

//     // 畫4*4個格子圍繞玩家
//     for (int i = -2; i <= 1; i++) {
//         for (int j = -2; j <= 1; j++) {
//             int drawX = (centerX + i) * textureSize;
//             int drawY = (centerY + j) * textureSize;
//             DrawTexture(grassland, drawX, drawY, WHITE);
//         }
//     }
// }

// void map_is_volcano(Hero* hero) {
//     //加載紋理1次
//     if (!volcanoLoaded) {
//         volcano = LoadTexture("resources/map/volcano.png");
//         volcanoLoaded = true;
//     }

//     int centerX = (int)(hero->position.x / textureSize);
//     int centerY = (int)(hero->position.y / textureSize);

//     // 畫4*4個格子圍繞玩家
//     for (int i = -2; i <= 1; i++) {
//         for (int j = -2; j <= 1; j++) {
//             int drawX = (centerX + i) * textureSize;
//             int drawY = (centerY + j) * textureSize;
//             DrawTexture(volcano, drawX, drawY, WHITE);
//         }
//     }
// }

// // 清除暫存中的紋理
// void map_cleanup_islandmap() {
//     if (islandLoaded) {
//         UnloadTexture(islandmap);
//         islandLoaded = false;
//     }
// }

// void map_cleanup_grassland() {
//     if (grasslandLoaded) {
//         UnloadTexture(grassland);
//         grasslandLoaded = false;
//     }
// }

// void map_cleanup_volcano() {
//     if (volcanoLoaded) {
//         UnloadTexture(volcano);
//         volcanoLoaded = false;
//     }
// }
