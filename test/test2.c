#include <raylib.h>
#include "../monster.h"

int main() {
  InitWindow(400, 800, "test2");

  SetTargetFPS(60);

  init_explosions();
  create_explosion(200, 400, RED);

  while (!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground(WHITE);
      draw_explosions();
    EndDrawing();
  
  }

  CloseWindow();
}
