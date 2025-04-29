#include"monster.h"
#include <raylib.h>
#include <stdlib.h>
#include "monster.h"
#include "collisionbox.h"
#include "hero.h"


#define INITIAL_MONSTER_COUNT 15  // 初始怪物數量//////////////
#define MAX_MONSTER_COUNT 150  // 最大怪物數量為150///////////
#define MONSTER_SPAWN_RATE 5  // 每次新增的怪物數量/////////////

// 添加遊戲時間相關變量（在全局變量部分）
#define MONSTER_SPAWN_INTERVAL 3.0f  // 每隔3秒生成一批怪物///////////////
float game_time = 0.0f;              // 遊戲進行時間（秒）///////////////////
float next_spawn_time = 3.0f;        // 下一次生成怪物的時間點//////////////

int dead_monster_count = 0;     // 死亡小怪數量計數器(每死十隻普通怪物就加一隻射擊怪物)

typedef struct {
    // Texture2D texture;
    CollisionBox box;
    int x, y;
    int width, height;
    int is_active;
    int health; 
    Color color;  // 射擊怪物顏色
} Monster;

Monster monsters[MAX_MONSTER_COUNT];//怪物的陣列
int current_monster_count = 0;  // 初始化為0，將在spawn_monsters函數中設置
int active_monster_count = 0;   // 當前活躍的怪物數量


void spawn_monsters() ;// 初始化怪物位置
void move_monsters_towards_player(Hero *hero);// 讓怪物追蹤玩家並從四周包圍
void add_monsters(Hero *hero);//新增新的怪物
void replace_missing_monsters(Hero *hero);//檢查並替換消失的怪物
void draw_monsters();






