#include <raylib.h>
#include <stdio.h>
#include "weapon.h"
#include "warrior.h"
#include "katana.h"


int main() {
  const int screenWidth = 1080;
  const int screenHeight = 960;

  InitWindow(screenWidth, screenHeight, "test");

  double timeDiff;
  double preTime = GetTime();
  double curTime = preTime;

  Warrior* warrior = WarriorInit();

  warrior->base.weapons[0] = &KatanaInit()->base;

  SetTargetFPS(60);

  while(!WindowShouldClose()) {

    curTime = GetTime();
    timeDiff = curTime - preTime;
    preTime = curTime;

    warrior->base.move(&warrior->base);

    BeginDrawing();
      warrior->base.draw(&warrior->base);
      ClearBackground(WHITE);
      warrior->base.update(&warrior->base, timeDiff);

      printf("The position of Hero is : (%f, %f)\n", warrior->base.position.x, warrior->base.position.y);
      printf("The position of weapon is: (%f, %f)\n", warrior->base.weapons[0]->position.x, warrior->base.weapons[0]->position.y);
      printf("The position of weapon's collsionbox is: (%f, %f)\n", ((Katana*)(warrior->base.weapons[0]))->box.rec.x, ((Katana*)(warrior->base.weapons[0]))->box.rec.y);
      printf("The cooltime of weapon is: %f\n", warrior->base.weapons[0]->curCooldownTime);

    EndDrawing();
  }

  printf("The width of the collstion box is %f\n", ((Katana*)warrior->base.weapons[0])->box.rec.width);
  printf("The height of the collstion box is %f\n", ((Katana*)warrior->base.weapons[0])->box.rec.height);

  CloseWindow();

}
