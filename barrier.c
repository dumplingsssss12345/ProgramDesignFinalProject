#include <raylib.h>
#include <stdlib.h>
#include "collisionbox.h"
#include "weapon.h"
#include "barrier.h"

#define BARRIER_OFFSET -20.0f

Barrier* BarrierInit() {
  Barrier* barrier = (Barrier*)malloc(sizeof(Barrier));
  char weaponName[51] = "Barrier";

  Weapon* base = WeaponInition(
    weaponName,                                            //武器名稱
    LoadTexture("resources/weapon/barrier.png"),           //武器貼圖
    5.0f,                                                  //攻擊力
    1.0f,                                                  //攻擊範圍
    20.0f,                                                 //攻擊速度
    0.0f,                                                  //冷卻時間
    (Vector2){0,0}                                         //初始位置
  );

  barrier->base = *base;
  free(base);

  barrier->base.attack = BarrierAttack;
  barrier->base.update = BarrierUpdate;
  barrier->base.destroy = BarrierDestroy;
  barrier->base.checkDemage = CheckBarrierDemage;

  barrier->circleCenter = (Vector2) {
    barrier->base.position.x + barrier->base.texture.width/2.0f + BARRIER_OFFSET,
    barrier->base.position.y + barrier->base.texture.height/2.0f + BARRIER_OFFSET,
  };
  barrier->radius = 200.0f;

  return barrier;
}

void BarrierAttack(Weapon* self) {
  Barrier* barrier = (Barrier*)self;

  //DrawTextureEx(barrier->base.texture, barrier->base.position, 0.0f, barrier->base.attackRange, WHITE);
  DrawTexturePro(
    barrier->base.texture,
    (Rectangle){0,0,barrier->base.texture.width,barrier->base.texture.height},
    (Rectangle){barrier->base.position.x,barrier->base.position.y,barrier->base.texture.width,barrier->base.texture.height},
    (Vector2){barrier->base.texture.width / 2,barrier->base.texture.height / 2},
    0,
    WHITE
  );
}

void BarrierUpdate(Weapon* self, double deltaTime) {
  Barrier* barrier = (Barrier*)self;

  //調整圓心位置
  barrier->circleCenter = (Vector2) {
    barrier->base.position.x + barrier->base.texture.width/2.0f + BARRIER_OFFSET,
    barrier->base.position.y + barrier->base.texture.height/2.0f + BARRIER_OFFSET,
  };

  //調整圓的半徑
  // barrier->radius *= barrier->base.attackRange;

  barrier->base.attack(&barrier->base);
}

void BarrierDestroy(Weapon *self) {
  Barrier* barrier = (Barrier*)self;

  free(barrier);
}

double CheckBarrierDemage(Weapon *self, struct CollisionBox *box) {
  Barrier* barrier = (Barrier*)self;
  double demage = 0.0f;

  /*if(CheckCollisionBoxAndCircle(*box, barrier->circleCenter, barrier->radius)) {
    demage += barrier->base.attackPower;
  }*/

  if(CheckCollisionBoxAndCircle(*box, barrier->base.position, barrier->radius)) {
    demage += barrier->base.attackPower;
  }

  return demage;
}

