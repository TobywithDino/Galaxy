#pragma once
#include "headers/level.h"
#include "headers/entity.h"
#include "headers/weapon.h"

enum class enemyType{
    sparkle,
    fort
};

class enemy : public entity{
public:
    enemy();
    ~enemy(){};
    static void createEnemy(enemyType eType, SDL_Renderer* renderer, position pos, int tier);
    static void createEnemy(enemyType eType, SDL_Renderer* renderer, int amount, int tier);
    void update(float fframeTime) override;
protected:
    weapon* enemyWeapon;
    void shoot(position to);
    position getRandomSquarePos(int from, int to);

    bool leaving;
    bool willLeave;
    int spawnTime;
    int stayTime;
    position leaveDir;
private:
    static position getRandomSpawnPos();
    static int enemyID;
};