#pragma once
#include <SDL2/SDL.h>
#include "headers/entity.h"

//also have active check system because im afraid that nullptr(entity* e) will cause error with no cautions.
class entity;
class collideEntity{
public:
    collideEntity(){
        active = false;
    };
    collideEntity(entity* e){
        this->e = e;
        this->lastCollideTime = SDL_GetTicks64();
        active = true;
    };
    ~collideEntity(){};
    bool isActive() {return active;};
    entity* getEnity() {return e;};
    Uint64 getLastCollideTime() {return lastCollideTime;};
    void setLastCollideTime(Uint64 t) {lastCollideTime = t;};
private:
    bool active;
    entity* e;
    Uint64 lastCollideTime;
};