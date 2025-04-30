#include "raylib.h"
#include "character_selection.h"
/*
請寫在遊戲 while(!windowshouldclose()){} 裡
顯示視窗、用按鍵Z X C選擇角色
回傳int值1、2、3
*/
int character_selc(){
    static int charac_code= -1;
    while(!WindowShouldClose()) {
        BeginDrawing();
            DrawText("choose your character use Z or X or C",10,130,20,DARKGRAY);
            switch (charac_code)
            {
            case 1:
                DrawText("your character code is 1",10,160,20,DARKGRAY);
                break;
            case 2:
                DrawText("your character code is 2",10,160,20,DARKGRAY);
                break;
            case 3:
                DrawText("your character code is 3",10,160,20,DARKGRAY);
                break;
            }
            if(IsKeyPressed(KEY_Z)){
                charac_code=1;
            }
            if(IsKeyPressed(KEY_X)){
                charac_code=2;
            }
            if(IsKeyPressed(KEY_C)){
                charac_code=3;
            }
        EndDrawing();

        if(charac_code != -1) {
            break;
        }
    }
    return charac_code;
}
