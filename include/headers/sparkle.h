#pragma once
#include "headers/enemy.h"

class sparkle : public enemy{
public:
    sparkle(SDL_Renderer* renderer, position pos);
    sparkle() {active = false;};
    ~sparkle() {};

    virtual void update(float fframeTime) override;

private:
    int chaseTime;
    Uint64 lastChaseTime;
    bool chasing;
    position moveDir;
    void chasePlayer(float fframeTime);
    int getRandomInt(int a, int b);
};