#include "headers/weapon.h"
#include <math.h>

weapon::weapon(){
    this->renderer = nullptr;
    this->bulletColType = collideType::playerBulletCollider;
    this->bulletTex = entityTex::pistolBulletTex;
    this->bulletDamage = 1;
    this->bulletSpeed = 70;
    this->bulletPenetrate = 1;
    this->bulletSize = 16;
    this->shootSpeed = 1.2;
    this->shootAccuracyRate = 1;
    this->recoil = 2;
    this->lastShootTime = 0;
    this->e = nullptr;
    this->shootPointOffset = 0;
    this->active = false;
}

void weapon::shoot(position to){
    int shotTimeGap = 1000*(1/shootSpeed);
    if(SDL_GetTicks64() - lastShootTime <= shotTimeGap) return;
    bullet::createBullet(e->getPos()+getShootPoint(to, 0), to, renderer, bulletColType, bulletTex, bulletDamage, bulletSpeed, bulletPenetrate, bulletSize, shootAccuracyRate);
    moveByRecoil(to - (e->getPos()+getShootPoint(to, 0)));
    lastShootTime = SDL_GetTicks64();
}

void weapon::moveByRecoil(position shootDir){
    /*
        NEED TO IMPORT ACCELERATION SYSTEM TO ENTITY.
    */

    // if(e == nullptr) return;
    // velocity recoilVel = entity::getNormalizedVelocity(recoil, e->getPos(), e->getPos() - shootDir);
    // e->setVel(recoilVel);
}

position weapon::getShootPoint(position to, float angle){
    position dir = to - e->getPos();
    float oriAngle = atan2(dir.y, dir.x) * ((float)180/3.14);
    angle += oriAngle;
    angle *= (3.14/(float)180);
    return position(shootPointOffset*cos(angle), shootPointOffset*sin(angle));
}