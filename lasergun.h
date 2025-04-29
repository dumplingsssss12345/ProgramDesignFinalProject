#include <raylib.h>
#include "collisionbox.h"
#include "weapon.h"

#ifndef LASERGUN_H
#define LASERGUN_H

/*--------------------------------------
調用LaserGunAttack時，會生成CollstionBox,並依據角色朝向射出長方形的激光
--------------------------------------*/
typedef struct LaserGun {
  Weapon base;                 //雷射槍的基本資訊
  CollisionBox box;            //碰撞槍，用以進行碰撞檢測
  double maxAttackTime;        //攻擊持續時間
  double curAttackTime;        //攻擊已持續時間
}LaserGun;

LaserGun* LaserGunInit();                                        //雷射槍的初始化函數
void LaserGunAttack(Weapon* self);                               //雷射槍的攻擊函數
void LaserGunUpdate(Weapon* self, double deltaTime);             //雷射槍的狀態更新函數
void LaserGunDestroy(Weapon* self);                              //雷射槍的銷毀函數
double CheckLaserGunDemage(Weapon* self, struct CollisionBox* box); //雷射槍的傷害碰撞函數

#endif
