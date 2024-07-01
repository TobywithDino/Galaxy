#pragma once
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "headers/position.h"
#include "headers/velocity.h"
#include "headers/acceleration.h"
#include "headers/collision.h"
#include "headers/collideEntity.h"

enum class entityTex{
    testEntityTex,
    playerTex,
    pistolBulletTex,
    machinegunBulletTex,
    sparkleTex,
    fortTex
};

enum class collideType; 
class entity{
public:
    entity();
    entity(SDL_Renderer* renderer, entityTex texName, position pos);
    ~entity() {};
    virtual void respawn(position pos);
    virtual void handleEvent(SDL_Event event);
    virtual void render();
    virtual void update(float fframeTime);
    void setPos(float x, float y) {pos.x = x; pos.y = y;};
    void setPos(position pos) {this->pos = pos;};
    void setVel(float xv, float yv) {vel.xv = xv; vel.yv = yv;};
    void setVel(velocity vel) {this->vel = vel;};
    void setAcce(float xa, float ya) {acce.xa = xa; acce.ya = ya;};
    void setAcce(acceleration acce) {this->acce = acce;};
    position getPos() {return pos;};
    velocity getVel() {return vel;};
    acceleration getAcce() {return acce;};
    int getDamage() {return damage;};
    int getHp() {return hp;};
    int getFullHp() {return fullHp;};
    int getSize() {return texSize;};
    float getCurrentSpeed();
    collideType getColType() {return colType;};
    bool isActive() {return active;};
    void hurtByEntity(entity* hit_e, int damage);
    void hurtByEntity(entity* hit_e, int damage, SDL_Color color, position wordPos);
    static acceleration getNormalizedAcceleration(float targetAccel, velocity from, velocity to);
    static velocity getNormalizedVelocity(float speed, position from, position to);
    virtual void upgrade(int tier);
protected:
    SDL_Texture* tex;
    SDL_Texture* getTexture(entityTex texName);
    SDL_Renderer* renderer;
    collideType colType;
    float speed;
    int hp;
    int fullHp;
    float hpRegen;
    int damage;
    position pos;
    velocity vel;
    acceleration acce;
    float frictionSpeedRatio;
    float accelerationSpeedRatio;
    int texSize;
    void destroy();
    bool active;
    virtual void accelerate(position dir, float fframeTime);
    int delayHurtTime;
    bool travelMap;
private:
    int lastHpRegenTime;
    void decelerate(float fframeTime);
    collideEntity* colEntity[10];
    int colEntityID;
    void initCollideEntity() {
        for(int i=0;i<10;i++) colEntity[i] = new collideEntity();
        colEntityID = 0;
    };
    void addCollideEntity(entity* e) {
        colEntity[colEntityID] = new collideEntity(e);
        this->colEntityID++;
        this->colEntityID %= 10;
    };
};