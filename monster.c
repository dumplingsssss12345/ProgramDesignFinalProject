#include"monster.h"
#include"hero.h"

Explosion explosions[MAX_EXPLOSIONS];  // 爆炸數組
int dx[4] = {-1, 1, 0, 0}; // 上下左右
int dy[4] = {0, 0, -1, 1};

// 隨機生成怪物位置，考慮2x2大小
Vector2 random_empty_position(Hero *hero) {
    double x = hero->position.x;
    double y =hero->position.y;
    double minDistance = 20;
    double maxDistance = 40;
    // do {
    //     pos->x = rand() % (MAP_HEIGHT - 1);  // 減1確保有足夠空間放置2x2怪物
    //     pos->y = rand() % (MAP_WIDTH - 1);   // 減1確保有足夠空間放置2x2怪物
        
    //     // 檢查2x2區域是否都是空的
    //     int valid = 1;
    //     for (int i = 0; i < 2 && valid; i++) {
    //         for (int j = 0; j < 2 && valid; j++) {
    //             int check_x = pos->x + i;
    //             int check_y = pos->y + j;
                
    //             // 檢查是否與玩家或障礙物重疊
    //             if (check_x >= MAP_HEIGHT || check_y >= MAP_WIDTH ||
    //                 map[check_x][check_y] == 1 ||
    //                 (check_x >= hero->position.x && check_x < hero->position.x + 2 && 
    //                  check_y >= hero->position.y && check_y < hero->position.y + 2)) {
    //                 valid = 0;
    //             }
    //         }
    //     }
        
    //     if (valid) break;
    // } while (1);

    //生成隨機角度
    double theta = ((double)rand() /RAND_MAX) * 2.0 * M_PI;

    //生成隨機半徑
    double minSquared = minDistance * minDistance;
    double maxSquared = maxDistance * maxDistance;
    double r = sqrt(minSquared + (maxSquared - minSquared) * ((double)rand() / RAND_MAX));

    //轉換為笛卡爾座標
    double resultX = x+r*cos(theta);
    double resultY = y+r*sin(theta);

    return (Vector2) {resultX, resultY};
}

// 初始化爆炸時設置默認半徑
void init_explosions() {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        explosions[i].is_active = false;
        explosions[i].radius = EXPLOSION_RADIUS; // 默認爆炸半徑
    }
}

// 創建新的爆炸
void create_explosion(int x, int y, Color color) {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        if (!explosions[i].is_active) {
            explosions[i].x = x;
            explosions[i].y = y;
            explosions[i].frame = 0;
            explosions[i].is_active = true;
            explosions[i].color = color;
            break;
        }
    }
}

// 绘制爆炸效果
void draw_explosions() {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        if (explosions[i].is_active) {
            // 计算爆炸当前的半径（随时间扩大，之后收缩）
            float progress = (float)explosions[i].frame / EXPLOSION_FRAMES;
            float radius;
            
            // 爆炸扩张和收缩的动画效果
            if (progress < 0.5f) {
                // 扩张阶段 (0->1->0.5)
                radius = explosions[i].radius * (progress * 2);
            } else {
                // 收缩阶段 (0.5->1->0)
                radius = explosions[i].radius * (2 - progress * 2);
            }
            
            // 绘制三个扩散圆环产生连续爆炸感
            Color outer_color = explosions[i].color;
            outer_color.a = 50; // 透明度较低
            
            Color mid_color = explosions[i].color;
            mid_color.a = 100;
            
            Color inner_color = explosions[i].color;
            inner_color.a = 200;
            
            // 绘制由外到内三个圆圈
            DrawCircle(explosions[i].y * CELL_SIZE + CELL_SIZE/2, 
                      explosions[i].x * CELL_SIZE + CELL_SIZE/2, 
                      radius * CELL_SIZE, outer_color);
                      
            DrawCircle(explosions[i].y * CELL_SIZE + CELL_SIZE/2, 
                      explosions[i].x * CELL_SIZE + CELL_SIZE/2, 
                      radius * CELL_SIZE * 0.7f, mid_color);
                      
            DrawCircle(explosions[i].y * CELL_SIZE + CELL_SIZE/2, 
                      explosions[i].x * CELL_SIZE + CELL_SIZE/2, 
                      radius * CELL_SIZE * 0.4f, inner_color);
                      
            // 在爆炸中心添加几个小圆点，增加爆炸感
            for (int j = 0; j < 8; j++) {
                float angle = j * (2 * PI / 8);
                float distance = radius * CELL_SIZE * 0.6f;
                float x = explosions[i].y * CELL_SIZE + CELL_SIZE/2 + cosf(angle) * distance;
                float y = explosions[i].x * CELL_SIZE + CELL_SIZE/2 + sinf(angle) * distance;
                
                DrawCircle(x, y, CELL_SIZE * 0.2f, WHITE);
            }
        }
    }
}
