#ifndef KATANA_H
#define KATANA_H

#include <raylib.h>
#include "weapon.h"
#include "collisionbox.h"

/*--------------------------------------
調用KatanaAttack時，會依據貼圖大小生成CollstionBox，並會依據角色朝向,從和朝向成直角的角度開始，揮舞attackAngle度的弧。
KatanaUpdate函數會不斷改變attackAngle，並且依據attackAngle去繪製武士刀的貼圖,並讓CollsionBox跟著貼圖移動。
--------------------------------------*/

typedef struct Katana {
  Weapon base;               //武士刀基本資訊
  CollisionBox box;          //碰撞箱，用以進行碰撞檢定
  double attackAngle;        //武士刀的揮舞弧度
  double maxAttackTime;        //攻擊持續時間
  double curAttackTime;        //攻擊已持續時間

}Katana;

Katana* KatanaInit();                                    //武士刀的初始化函數
void KatanaAttack(Weapon* self);                        //武士刀的攻擊函數
void KatanaUpdate(Weapon* self, double deltaTime);       //武士刀的狀態更新函數
void KatanaDestroy(Weapon* self);                       //武士刀的銷毀函數
double CheckKatanaDemage(Weapon* self, struct CollisionBox* box); //武士刀的傷害碰撞函數

#endif

