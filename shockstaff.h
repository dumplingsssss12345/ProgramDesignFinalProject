#ifndef SHOCKSTAFF_H
#define SHOCKSTAFF_H

#include <raylib.h>
#include "weapon.h"

/*--------------------------------------
調用ShockStaffAttack時，鎮集杖會依據角色的位置，在角色的中心處生成一個半徑為radius的沖擊波，並擊退此範圍內的敵人。
radius會根據attackRange進行調整。
--------------------------------------*/


typedef struct ShockStaff{
  Weapon base;                      //震擊杖的基本資訊
  double radius;                    //震擊杖的攻擊半徑
}ShockStaff;

void ShockStaffAttack(Weapon* self);                        //震擊杖的攻擊函數
void ShockStaffUpdate(Weapon* self, float deltaTime);       //震擊杖的狀態更新函數
void ShockStaffDestroy(Weapon* slef);                       //震擊杖的銷毀函數
double CheckShockStaffDemage(Weapon* self, struct CollsionBox box); //震擊杖的傷害碰撞函數
#endif
