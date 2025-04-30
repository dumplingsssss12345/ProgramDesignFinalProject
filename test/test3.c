#include <raylib.h>
#include <stdio.h>
#include "../basic_monster.h"
#include "../monster.h"
#include "../weapon.h"
#include "../warrior.h"
#include "../lasergun.h"

int main() {
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "test3");

  Warrior* warrior = WarriorInit();
  spawn_monsters();
  init_explosions();

  double preTime = GetTime();
  double curTime = preTime;
  double timeDiff;

  SetTargetFPS(60);

  while(!WindowShouldClose()) {
    curTime = GetTime();
    timeDiff = curTime - preTime;
    preTime = curTime;

    add_monsters(&warrior->base);
    move_monsters_towards_player(&warrior->base);

    warrior->base.move(&warrior->base);
    BeginDrawing();
      ClearBackground(WHITE);

      draw_monsters();
      warrior->base.draw(&warrior->base);
      warrior->base.update(&warrior->base, timeDiff);
      check_collision(&warrior->base);

    EndDrawing();
    // printf("The position of first monst is : (%f,%f)\n", monsters[0].x, monsters[0].y);
    // printf("The position of first monst's collision box is : (%f,%f)\n", monsters[0].box.rec.x, monsters[0].box.rec.y);
    
  }
}

