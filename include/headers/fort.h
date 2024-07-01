#pragma once
#include "headers/enemy.h"

class fort : public enemy{
public:
    fort(SDL_Renderer* renderer, position pos);
    fort() {active = false;};
    ~fort() {};

    virtual void update(float fframeTime) override;
private:
    position sitePos;
    position getSitePos();
    void moveToSite(float fframeTime);
    bool checkOnSite();
    bool moving;
    Uint64 lastMoveTime;
    int moveGapTime;
};