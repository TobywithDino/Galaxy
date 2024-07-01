#include "headers/bar.h"

int bar::barID;

bar::bar(){
    this->e = nullptr;
    this->active = false;
}

bar::bar(position pos, SDL_Color baseColor, SDL_Color barColor, entity* e, int width_ratio, int height_ratio, bool disappear, SDL_Renderer* renderer){
    this->pos = pos;
    this->baseColor = baseColor;
    this->barColor = barColor;
    this->e = e;
    this->width_ratio = width_ratio;
    this->height_ratio = height_ratio;
    this->renderer = renderer;
    this->deathTime = SDL_GetTicks64();
    this->disappear = disappear;
    active = true;
}

void bar::update(position pos){
    if(!active || e == nullptr) return;
    this->pos = pos;
    if(disappear && SDL_GetTicks64() - deathTime > lifeSpan) this->active = false;
}

void bar::render(){
    if(!active) return;
    SDL_Rect base_dst;
    base_dst.w = width_ratio * game::scale * e->getFullHp();
    base_dst.h = height_ratio * game::scale;
    base_dst.x = pos.x - base_dst.w/2;
    base_dst.y = pos.y - base_dst.h/2;
    SDL_SetRenderDrawColor(renderer, baseColor.r, baseColor.g, baseColor.b, baseColor.a);
    SDL_RenderFillRect(renderer, &base_dst);
    
    SDL_Rect bar_dst;
    bar_dst.w = width_ratio * game::scale * e->getHp();
    bar_dst.h = height_ratio * game::scale;
    bar_dst.x = base_dst.x;
    bar_dst.y = base_dst.y;
    SDL_SetRenderDrawColor(renderer, barColor.r, barColor.g, barColor.b, barColor.a);
    SDL_RenderFillRect(renderer, &bar_dst);
}

void bar::createDisappearBar(position pos, SDL_Color baseColor, SDL_Color barColor, entity* e, int width_ratio, int height_ratio, SDL_Renderer* renderer){
    game::barGroup[barID] = new bar(pos, baseColor, barColor, e, width_ratio, height_ratio, true, renderer);
    barID++;
    barID %= game::maxBars;
}