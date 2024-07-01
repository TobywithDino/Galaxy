#pragma once
#include "headers/collision.h"
#include "headers/position.h"
#include "headers/velocity.h"
#include "headers/bullet.h"
#include "headers/entity.h"
#include <SDL2/SDL.h>

enum class weaponType{
    pistol,
    rifle,
    shotgun,
    splitter
};


class weapon{
public:
    weapon();
    ~weapon(){};

    virtual void shoot(position to);
    bool isActive() {return active;};
protected:
    void moveByRecoil(position shootDir);
    position getShootPoint(position to, float angle);
    
    SDL_Renderer* renderer;
    collideType bulletColType;
    entityTex bulletTex;
    int bulletDamage;
    float bulletSpeed;
    int bulletPenetrate;
    int bulletSize;
    float shootSpeed;
    float shootAccuracyRate;
    float recoil;
    Uint64 lastShootTime;
    entity* e;
    float shootPointOffset;
    bool active;
};