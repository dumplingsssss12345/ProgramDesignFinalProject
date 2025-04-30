#ifndef HERO_H
#define HERO_H

#include <raylib.h>
#include "weapon.h"
#include "collisionbox.h"

typedef struct Hero{
  char name[51];                   //英雄名稱

  Vector2 position;                //英雄位置
  Vector2 direction;               //英雄目前的朝向
  Texture2D texture;               //英雄的貼圖
  CollisionBox box;                //碰撞箱，用於執行碰撞檢測

  Weapon* weapons[6];              //英雄目前持有的武器
  unsigned int weaponCount;        //英雄目前的武器數量，上限為6

  double speed;                    //英雄的移動速度
  double maxHp;                    //英雄的血量上限
  double hp;                       //英雄的血量
  double attackPower;              //角色攻擊力
  double pickupRadius;             //英雄的拾取半徑
  double hpRecoveryRate; // 每秒回血量
  int level;             // 等級
  int exp;               // 經驗值
  int nextLevelExp;      // 升下個等級需要的經驗值

  void (*move)(struct Hero* self);                     //角色移動
  void (*draw)(struct Hero* self);                     //角色的繪製函數
  void (*update)(struct Hero* self, double deltaTime); //角色狀態更新
  void (*destroy)(struct Hero* self);                  //角色銷毀函數,將角色從記憶體中刪除
}Hero;

Hero* HeroInit(char name[51], Vector2 position, Texture2D texture, double attackPower, double speed, double maxHp, double hpRecoveryRate, double pickRadius);   //角色初始化函數

void HeroMove(Hero* self);                                   //依照輸入決定角色移動
void HeroDraw(Hero* self);                                   //繪製角色貼圖
void HeroUpdate(Hero* self, double deltaTime);               //更新角色狀態（武器冷卻時間等）
void HeroDestroy(Hero* self);                                //角色銷毀函數
double CheckDemage(CollisionBox* box, Hero* self);           //傷害檢查函數，此函數會將傳進來的collsionbox與weapons的攻擊範圍進行檢查，檢查完畢後會傳回受到的總傷害

#endif
