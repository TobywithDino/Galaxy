#include "headers/pistol.h"

pistol::pistol(SDL_Renderer* renderer, entity* e, float shootPointOffset, collideType colType){
    weapon();
    this->renderer = renderer;
    this->bulletColType = colType;
    this->bulletTex = entityTex::pistolBulletTex;
    this->bulletDamage = 1;
    this->bulletSpeed = 100;
    this->bulletPenetrate = 1;
    this->bulletSize = 16;
    this->shootSpeed = 2.2;
    this->shootAccuracyRate = 1;
    this->recoil = 8;
    this->lastShootTime = 0;
    this->e = e;
    this->shootPointOffset = shootPointOffset;
    this->active = true;
}

void pistol::shoot(position to){
    int shotTimeGap = 1000*(1/shootSpeed);
    if(SDL_GetTicks64() - lastShootTime <= shotTimeGap) return;
    position newShootPoint1 = e->getPos()+getShootPoint(to, 75);
    position newShootPoint2 = e->getPos()+getShootPoint(to, -75);
    bullet::createBullet(newShootPoint1, to+(newShootPoint1-e->getPos()), renderer, bulletColType, bulletTex, bulletDamage, bulletSpeed, bulletPenetrate, bulletSize, shootAccuracyRate);
    bullet::createBullet(newShootPoint2, to+(newShootPoint2-e->getPos()), renderer, bulletColType, bulletTex, bulletDamage, bulletSpeed, bulletPenetrate, bulletSize, shootAccuracyRate);
    // moveByRecoil(to - (e->getPos()+getShootPoint(to, 0)));
    lastShootTime = SDL_GetTicks64();
}