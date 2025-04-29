#ifndef WHIP_H
#define WHIP_H

#include <raylib.h>
#include "collisionbox.h"
#include "weapon.h"

/*--------------------------------------
調用WhipAttack時,會在玩家的水平方向生成鞭子的水平特效,並生成CollsionBox,傷害範圍內的敵人。
--------------------------------------*/

typedef struct Whip {
  Weapon base;          //紀錄鞭子的基本資訊
  CollisionBox box;     //碰撞箱,用以進行碰撞檢測
  double curAttackTime;
  double maxAttackTime;
}Whip;

Whip* WhipInit();                                     //鞭子的生成函數
void WhipAttack(Weapon* self);                        //鞭子的攻擊函數
void WhipUpdate(Weapon* self, double deltaTime);       //鞭子的狀態更新函數
void WhipDestroy(Weapon* slef);                       //鞭子的銷毀函數
double CheckWhipDemage(Weapon* self, struct CollisionBox* box); //鞭子的傷害碰撞函數


#endif 
