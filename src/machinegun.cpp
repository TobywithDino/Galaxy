#include "headers/machinegun.h"

machinegun::machinegun(SDL_Renderer* renderer, entity* e, float shootPointOffset, collideType colType){
    weapon();
    this->renderer = renderer;
    this->bulletColType = colType;
    this->bulletTex = entityTex::machinegunBulletTex;
    this->bulletDamage = 1;
    this->bulletSpeed = 40;
    this->bulletPenetrate = 1;
    this->bulletSize = 8;
    this->shootSpeed = 3;
    this->shootAccuracyRate = 0.3;
    this->recoil = 8;
    this->lastShootTime = 0;
    this->e = e;
    this->shootPointOffset = shootPointOffset;
    this->active = true;
}