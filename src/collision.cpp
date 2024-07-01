#include "headers/collision.h"
#include "headers/game.h"
#include "headers/text.h"
#include <iostream>
#include <math.h>

void collision::addColliders(entity** e){
    colliders.emplace_back(e);
}

void collision::collisionUpdate(){
    for(int i=0;i<colliders.size()-1;i++){
        for(int j=i+1;j<colliders.size();j++){
            check(*colliders[i], *colliders[j]);
        }
    }
}

void collision::check(entity* e1, entity* e2){
    float e1RealHalfSize = e1->getSize() * game::scale / 2;
    float e2RealHalfSize = e2->getSize() * game::scale / 2;
    if(getDistance(e1, e2) >e1RealHalfSize+e2RealHalfSize || !e1->isActive() || !e2->isActive()) return;
    float r = e1RealHalfSize+e2RealHalfSize;
    float x = (e1RealHalfSize * e2->getPos().x + e2RealHalfSize * e1->getPos().x) / r;
    float y = (e1RealHalfSize * e2->getPos().y + e2RealHalfSize * e1->getPos().y) / r;
    position collidePos = position(x,y);

    collideType co1, co2;
    co1 = e1->getColType();
    co2 = e2->getColType();

    if(co1 == collideType::playerCollider){
        if(co2 == collideType::enemyCollider){
            e1->hurtByEntity(e2, e2->getDamage(), text::playerHurtTextColor, collidePos);
            e2->hurtByEntity(e1, e1->getDamage(), text::enemyHurtTextColor, collidePos);
        }
        if(co2 == collideType::enemyBulletCollider){
            e1->hurtByEntity(e2, e2->getDamage(), text::playerHurtTextColor, collidePos);
            e2->hurtByEntity(e1, 1);
        }
    }
    if(co1 == collideType::enemyCollider){
        if(co2 == collideType::playerCollider){
            e1->hurtByEntity(e2, e2->getDamage(), text::enemyHurtTextColor, collidePos);
            e2->hurtByEntity(e1, e1->getDamage(), text::playerHurtTextColor, collidePos);
        }
        if(co2 == collideType::playerBulletCollider){
            e1->hurtByEntity(e2, e2->getDamage(), text::enemyHurtTextColor, collidePos);
            e2->hurtByEntity(e1, 1);
        }
    }
    if(co1 == collideType::playerBulletCollider){
        if(co2 == collideType::enemyCollider){
            e1->hurtByEntity(e2, 1);
            e2->hurtByEntity(e1, e1->getDamage(), text::enemyHurtTextColor, collidePos);
        }
    }
    if(co1 == collideType::enemyBulletCollider){
        if(co2 == collideType::playerCollider){
            e1->hurtByEntity(e2, 1);
            e2->hurtByEntity(e1, e1->getDamage(), text::playerHurtTextColor, collidePos);
        }
    }
}

float collision::getDistance(entity* e1, entity* e2){
    float x = e1->getPos().x - e2->getPos().x;
    float y = e1->getPos().y - e2->getPos().y;
    float dis = sqrt(x*x + y*y);
    return dis;
}