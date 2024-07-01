#pragma once
#include <SDL2/SDL.h>
#include "headers/position.h"
#include "headers/game.h"

class bar{
public:
    bar(position pos, SDL_Color baseColor, SDL_Color barColor, entity* e, int width_ratio, int height_ratio, bool disappear, SDL_Renderer* renderer);
    bar();
    ~bar(){};

    void render();
    void update(position pos);
    void setActive(bool isActive) {active = isActive;};
    bool isActive() {return active;};
    position getPos() {return pos;};

    static void createDisappearBar(position pos, SDL_Color baseColor, SDL_Color barColor, entity* e, int width_ratio, int height_ratio, SDL_Renderer* renderer);
private:
    position pos;
    SDL_Color baseColor;
    SDL_Color barColor;
    entity* e;
    bool active;

    int width_ratio;
    int height_ratio;

    Uint64 deathTime;
    const int lifeSpan = 3000;//milliseconds
    bool disappear;

    SDL_Renderer* renderer;
    static int barID;
};