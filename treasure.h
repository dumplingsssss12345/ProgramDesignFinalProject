#ifndef TREASURE_H
#define TREASURE_H

#include <stdbool.h>
#include "raylib.h"
#include "collisionbox.h"

// 前置宣告
typedef struct Hero Hero;

typedef struct {
    Vector2 position;
    bool is_opened;
    CollisionBox hitbox;
    Texture2D closedTexture;   // 未開啟時的貼圖
    Texture2D openedTexture;   // 開啟後的貼圖
} Treasure;


// 寶箱系統初始化（遊戲開始時呼叫）
void Treasure_InitSystem(void);

// 怪物被擊殺時呼叫，負責計數與生成寶箱
void Treasure_OnMonsterKilled(Hero* hero);

// 每幀更新寶箱狀態，處理玩家碰撞與開啟寶箱
int Treasure_Update(Hero* hero);

// 繪製所有寶箱
void Treasure_DrawAll(void);

// 釋放所有寶箱資源（遊戲結束或切換場景時呼叫）
void Treasure_DestroyAll(void);

#endif

