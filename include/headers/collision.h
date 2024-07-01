#pragma once
#include "headers/entity.h"
#include <vector>

class entity;
enum class collideType{
    entityCollider,
    playerCollider,
    enemyCollider,
    playerBulletCollider,
    enemyBulletCollider
};

class collision{
public:
    collision(){};
    ~collision(){};
    void addColliders(entity** e);
    void collisionUpdate();
private:
    void check(entity* e1, entity* e2);
    float getDistance(entity* e1, entity* e2);
    std::vector<entity**> colliders;
};