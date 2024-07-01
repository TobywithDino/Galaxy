#pragma once
#include "headers/entity.h"

class bullet : public entity{
public:
    bullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size);
    bullet(){active = false;};
    ~bullet(){};

    virtual void update(float fframeTime) override;
    static void createBullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size);
    static void createBullet(position from, position to, SDL_Renderer* renderer, collideType colType, entityTex texName, int damage, float speed, int hp, int size, float accuracyRate);

private:
    static int bulletID;
    Uint64 birthTime;
    const int lifeSpan = 10000;//milliseconds

    static position getRandomAngleDir(position dir);
};