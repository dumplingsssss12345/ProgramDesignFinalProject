#include"hero.h"
#include"basic_monster.h"
#include"collisionbox.h"
#include"shooter_monster.h"


// 初始化射擊型怪物
void init_shooter_monsters() {
    for (int i = 0; i < MAX_SHOOTER_MONSTERS; i++) {
        shooter_monsters[i].is_active = 0;
        shooter_monsters[i].cooldown = 0;
    }
}

// 初始化射擊物
void init_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        projectiles[i].is_active = false;
    }
}

// // 創建新射擊物
// void create_projectile(int x, int y, int direction, Color color) {
//     for (int i = 0; i < MAX_PROJECTILES; i++) {
//         if (!projectiles[i].is_active) {
//             projectiles[i].x = x;
//             projectiles[i].y = y;
//             projectiles[i].direction = direction;
//             projectiles[i].range_left = PROJECTILE_RANGE; // 設為10格射程
//             projectiles[i].is_active = true;
//             projectiles[i].color = PURPLE_BLUE; // 固定使用紫藍色
//             break;
//         }
//     }
// }

// 創建新射擊物
void create_projectile(int x, int y, int direction, Color color) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (!projectiles[i].is_active) {
            projectiles[i].position.x=x;
            projectiles[i].position.y=y;
            // projectiles[i].x = x;
            // projectiles[i].y = y;
            projectiles[i].direction = direction;
            projectiles[i].range_left = PROJECTILE_RANGE; // 設為10格射程
            projectiles[i].is_active = true;
            projectiles[i].color = PURPLE_BLUE; // 固定使用紫藍色

            projectiles[i].box.rec.x=projectiles[i].position.x;
            projectiles[i].box.rec.y=projectiles[i].position.y;
            projectiles[i].box.rotationAngle=0.0f;
            break;
        }
    }
}

void spawn_shooter_monster(Hero *hero) {
    if (dead_monster_count >= DEAD_MONSTERS_TO_SPAWN_SHOOTER) {// 檢查是否需要生成射擊型怪物
        if (current_shooter_count < MAX_SHOOTER_MONSTERS) {
            Node pos;
            random_empty_position(&pos,hero);
            
            for (int i = 0; i < MAX_SHOOTER_MONSTERS; i++) {
                if (!shooter_monsters[i].is_active) {
                    shooter_monsters[i].x = pos.x;
                    shooter_monsters[i].y = pos.y;
                    shooter_monsters[i].is_active = 1;
                    shooter_monsters[i].color = ORANGE;  // 射擊怪物使用橙色
                    shooter_monsters[i].cooldown = 30;   // 初始冷卻時間
                    shooter_monsters[i].width=20;
                    shooter_monsters[i].height=20;
                    shooter_monsters[i].health=300;
                    current_shooter_count++;
    
                    shooter_monsters[i].box.rec.x=shooter_monsters[i].x;
                    shooter_monsters[i].box.rec.y=shooter_monsters[i].y;
                    shooter_monsters[i].box.rec.width=shooter_monsters[i].width;
                    shooter_monsters[i].box.rec.height=shooter_monsters[i].height;
                    
                    return;
                }
            }
        }

        dead_monster_count = 0;  // 重置計數器
    }
     
}

// 移動射擊型怪物和處理射擊
void update_shooter_monsters(Hero *hero) {
    for (int i = 0; i < MAX_SHOOTER_MONSTERS; i++) {
        if (!shooter_monsters[i].is_active) continue;
        
        // 降低移動頻率
        if (rand() % 100 >= MONSTER_MOVE_CHANCE) {
            // continue;

            int monster_x = shooter_monsters[i].x;
            int monster_y = shooter_monsters[i].y;
            
            // 簡單追蹤玩家行為
            if (monster_x < hero->position.x) shooter_monsters[i].x++;
            else if (monster_x > hero->position.x) shooter_monsters[i].x--;
            
            if (monster_y < hero->position.y) shooter_monsters[i].y++;
            else if (monster_y > hero->position.y) shooter_monsters[i].y--;
            
            // 檢查新位置是否有效
            int valid = 1;
            for (int dx = 0; dx < 2 && valid; dx++) {
                for (int dy = 0; dy < 2 && valid; dy++) {
                    int check_x = shooter_monsters[i].x + dx;
                    int check_y = shooter_monsters[i].y + dy;
                    
                    if (check_x < 0 || check_y < 0 || check_x >= MAP_HEIGHT || check_y >= MAP_WIDTH || map[check_x][check_y] == 1) {
                        valid = 0;
                    }
                }
            }
            
            if (!valid) {
                shooter_monsters[i].x = monster_x;  // 恢復原始位置
                shooter_monsters[i].y = monster_y;
            }
        }
        
        //更新碰撞箱
        shooter_monsters[i].box.rec.x=shooter_monsters[i].x;
        shooter_monsters[i].box.rec.y=shooter_monsters[i].y;
        shooter_monsters[i].box.rec.width=shooter_monsters[i].width;
        shooter_monsters[i].box.rec.height=shooter_monsters[i].height;
        
        if (shooter_monsters[i].cooldown == 0 && (rand() % 100 > SHOOTER_FIRE_CHANCE) ) {

            for (int dir = 0; dir < 4; dir++) {
                create_projectile(shooter_monsters[i].x, shooter_monsters[i].y, dir, PURPLE_BLUE);
            }

            // 減少冷卻時間
            if (shooter_monsters[i].cooldown > 0) {
                shooter_monsters[i].cooldown--;
            }
        }   
    }
}

//創建指定半徑的爆炸(射擊型怪物)
void create_explosion_with_radius(int x, int y, Color color, int radius) {
    for (int i = 0; i < MAX_EXPLOSIONS; i++) {
        if (!explosions[i].is_active) {
            explosions[i].x = x;
            explosions[i].y = y;
            explosions[i].frame = 0;
            explosions[i].is_active = true;
            explosions[i].color = color;
            explosions[i].radius = radius; // 添加爆炸半徑屬性

            break;
        }
    }
}


// 檢查玩家是否在爆炸範圍內
bool check_player_in_explosion_radius(int explosion_x, int explosion_y, int radius,Hero *hero) {
    Vector2 circle;
    circle.x=explosion_x;
    circle.y=explosion_y;
    bool result=CheckCollisionBoxAndCircle(hero->box,circle,6);// 檢查玩家是否有在爆炸範圍內
    if(result==1) return true;// 玩家在爆炸範圍內
    else return false;// 玩家不在爆炸範圍內
}


// 移動射擊型怪物和處理射擊
void update_shooter_monsters(Hero *hero) {
    for (int i = 0; i < MAX_SHOOTER_MONSTERS; i++) {
        if (!shooter_monsters[i].is_active) continue;
        
        // 降低移動頻率
        if (rand() % 100 >= MONSTER_MOVE_CHANCE) {
            // continue;

            int monster_x = shooter_monsters[i].x;
            int monster_y = shooter_monsters[i].y;
            
            // 簡單追蹤玩家行為
            if (monster_x < hero->position.x) shooter_monsters[i].x++;
            else if (monster_x > hero->position.x) shooter_monsters[i].x--;
            
            if (monster_y < hero->position.y) shooter_monsters[i].y++;
            else if (monster_y > hero->position.y) shooter_monsters[i].y--;

            // 檢查新位置是否有效
            int valid = 1;
            for (int dx = 0; dx < 2 && valid; dx++) {
                for (int dy = 0; dy < 2 && valid; dy++) {
                    int check_x = shooter_monsters[i].x + dx;
                    int check_y = shooter_monsters[i].y + dy;
                    
                    if (check_x < 0 || check_y < 0 || check_x >= MAP_HEIGHT || check_y >= MAP_WIDTH || map[check_x][check_y] == 1) {
                        valid = 0;
                    }
                }
            }
            
            if (!valid) {
                shooter_monsters[i].x = monster_x;  // 恢復原始位置
                shooter_monsters[i].y = monster_y;
            }

        }
        
        int monster_x = shooter_monsters[i].x;
        int monster_y = shooter_monsters[i].y;
        
        if (shooter_monsters[i].cooldown == 0 && (rand() % 100 > SHOOTER_FIRE_CHANCE) ) {

            for (int dir = 0; dir < 4; dir++) {
                create_projectile(shooter_monsters[i].x, shooter_monsters[i].y, dir, PURPLE_BLUE);
            }
            shooter_monsters[i].cooldown = 60;  // 冷卻時間約1秒
        }
        
        // 減少冷卻時間
        if (shooter_monsters[i].cooldown > 0) {
            shooter_monsters[i].cooldown--;
        }
        
    }
}


// 火焰射擊物更新函數
void update_projectiles(Hero *hero) {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (!projectiles[i].is_active) continue;
        
        // 更新位置
        switch(projectiles[i].direction) {
            case 0: // 上
                projectiles[i].x--;
                break;
            case 1: // 下
                projectiles[i].x++;
                break;
            case 2: // 左
                projectiles[i].y--;
                break;
            case 3: // 右
                projectiles[i].y++;
                break;
        }

        //更新碰撞箱
        projectiles[i].box.rec.x=projectiles[i].x;
        projectiles[i].box.rec.y=projectiles[i].y;
        
        // 減少剩餘射程
        projectiles[i].range_left--;

        // 檢查是否超出地圖或撞到障礙物或射程耗盡
        bool should_explode = false;
        
        // 檢查是否超出地圖或撞到障礙物
        if (projectiles[i].x < 0 || projectiles[i].y < 0 || 
            projectiles[i].x >= MAP_HEIGHT || projectiles[i].y >= MAP_WIDTH || 
            map[projectiles[i].x][projectiles[i].y] == 1 || 
            projectiles[i].range_left <= 0) {
            
                should_explode = true;
        }
        
        // 檢查是否擊中玩家（考慮2x2玩家大小）
        bool hit_player = false;
        // for (int px = 0; px < 2 && !hit_player; px++) {
        //     for (int py = 0; py < 2 && !hit_player; py++) {
        //         if (hero->position.x + px == projectiles[i].x && hero->position.y + py == projectiles[i].y) {
        //             hit_player = true;
        //             should_explode = true;
        //         }
        //     }
        // }
        bool result=CheckCollisionBoxAndCircle(hero->box, projectiles[i].position,3);
        if(result==1){
            hit_player = true;
            should_explode = true;
        }

        // 如果需要爆炸
        if (should_explode) {
            // 創建鮮豔紫藍色爆炸效果
            create_explosion_with_radius(projectiles[i].x, projectiles[i].y, PURPLE_BLUE, 6);
            projectiles[i].is_active = false;
            
            // 檢查玩家是否在爆炸範圍內
            bool player_in_explosion = check_player_in_explosion_radius(projectiles[i].x, projectiles[i].y, 6,hero);
            if (hit_player || player_in_explosion) {
                hero->hp-=50;
                
                // 如果生命值耗盡，直接返回
                if (hero->hp <= 0) return;
            }
            
            continue;
        }
    }
}

// 绘制射击型怪物
void draw_shooter_monsters() {
    for (int i = 0; i < MAX_SHOOTER_MONSTERS; i++) {
        if (shooter_monsters[i].is_active) {
            // 绘制主体为橙色的怪物，有特殊标记
            DrawRectangle(shooter_monsters[i].y * CELL_SIZE, shooter_monsters[i].x * CELL_SIZE, 
                        CELL_SIZE * 2, CELL_SIZE * 2, ORANGE);
            
            // 增加特殊标记（例如中间有个圆形）
            DrawCircle(shooter_monsters[i].y * CELL_SIZE + CELL_SIZE, 
                    shooter_monsters[i].x * CELL_SIZE + CELL_SIZE, 
                    CELL_SIZE * 0.6f, RED);
        }
    }
}



// 绘制射击物（火焰）
void draw_projectiles() {
    for (int i = 0; i < MAX_PROJECTILES; i++) {
        if (projectiles[i].is_active) {
            // 火焰主体 - 紫蓝色
            Color flame = PURPLE_BLUE;
            // 根据射程剩余量调整透明度
            flame.a = 180 + (unsigned char)(75.0f * projectiles[i].range_left / PROJECTILE_RANGE);
            
            // 绘制火焰效果 - 主体为紫蓝色，半径为3
            DrawCircle(projectiles[i].y * CELL_SIZE + CELL_SIZE/2,
                    projectiles[i].x * CELL_SIZE + CELL_SIZE/2,
                    CELL_SIZE * 0.3f * 3, flame); // 半径为3
                    
            // 火焰内核 - 较亮的紫蓝色
            Color inner_flame = (Color){ 150, 120, 255, 255 };
            DrawCircle(projectiles[i].y * CELL_SIZE + CELL_SIZE/2,
                    projectiles[i].x * CELL_SIZE + CELL_SIZE/2,
                    CELL_SIZE * 0.2f * 3, inner_flame);
            
            // 火焰中心 - 最亮
            Color core = (Color){ 200, 180, 255, 255 };
            DrawCircle(projectiles[i].y * CELL_SIZE + CELL_SIZE/2,
                    projectiles[i].x * CELL_SIZE + CELL_SIZE/2,
                    CELL_SIZE * 0.1f * 3, core);
                    
            // 添加火焰方向指示
            int tail_x = projectiles[i].x;
            int tail_y = projectiles[i].y;
            
            // 根据方向绘制火焰尾巴
            switch(projectiles[i].direction) {
                case 0: tail_x += 1; break; // 上
                case 1: tail_x -= 1; break; // 下
                case 2: tail_y += 1; break; // 左
                case 3: tail_y -= 1; break; // 右
            }
            
            // 绘制尾巴
            if (tail_x >= 0 && tail_y >= 0 && tail_x < MAP_HEIGHT && tail_y < MAP_WIDTH) {
                Color tail = PURPLE_BLUE;
                tail.a = 100;
                DrawCircle(tail_y * CELL_SIZE + CELL_SIZE/2,
                        tail_x * CELL_SIZE + CELL_SIZE/2,
                        CELL_SIZE * 0.15f * 3, tail);
            }
        }
    }
}