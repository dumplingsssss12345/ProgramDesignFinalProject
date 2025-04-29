#include <raylib.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// 怪物移動間隔設定
#define MONSTER_MOVE_CHANCE 97  // 越大怪物移動越慢 (1-100)

#define CELL_SIZE 10

// 爆炸效果設定
#define MAX_EXPLOSIONS 10  // 同時存在的最大爆炸數量
#define EXPLOSION_FRAMES 15  // 爆炸動畫的總幀數
#define EXPLOSION_RADIUS 8  // 爆炸的半徑
// 爆炸結構
typedef struct {
    CollisionBox box;
    int x, y;           // 爆炸中心點
    int frame;          // 當前爆炸幀
    bool is_active;     // 爆炸是否活躍
    Color color;        // 爆炸顏色
    int radius;         // 爆炸半徑
} Explosion;
Explosion explosions[MAX_EXPLOSIONS];  // 爆炸數組


// 方向移動
int dx[4] = {-1, 1, 0, 0}; // 上下左右
int dy[4] = {0, 0, -1, 1};

typedef struct {
    int x, y;
} Node;//怪物座標

void random_empty_position(Node* pos,Hero *hero);// 隨機生成怪物位置，考慮2x2大小

//爆炸相關
void init_explosions();//初始化爆炸
void create_explosion(int x, int y, Color color);//創建爆炸
void draw_explosions();//繪製爆炸












