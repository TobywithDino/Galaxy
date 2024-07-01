#pragma once
#include <SDL2/SDL_ttf.h>
#include <vector>
#include <iostream>
#include "headers/player.h"
#include "headers/button.h"
#include "headers/bar.h"

class word{
public:
    word(position* pos, float size, std::string text, SDL_Color color, SDL_Renderer* renderer, bool disappear);
    word():active(false), disappear(false){};
    ~word(){};
    void render();
    void update(position* pos);
    position* getPos() {return pos;};
    std::string getText() {return text;};
    void setPos(position* pos) {this->pos = pos;};
    void setText(std::string newText);
private:
    position* pos;
    float size;
    std::string text;
    SDL_Color color;
    SDL_Texture* tex;
    SDL_Renderer* renderer;
    bool disappear;
    Uint64 birthTime;
    int lifeSpan;//milliseconds
    bool active;
};

class bar;
class text{
public:
    text(){};
    ~text(){};
    void init(SDL_Renderer* renderer);
    void handleEvent(SDL_Event e);
    void update();
    void render();
    static SDL_Texture* getTextTexture(SDL_Renderer* renderer, TTF_Font* font, std::string text, SDL_Color color);
    static void creatDisappearWord(position* pos, float size, std::string text, SDL_Color color, SDL_Renderer* renderer);
    static TTF_Font* font; 
    static int wordID;
    static constexpr SDL_Color menuTextColor = {40, 40, 40};
    static constexpr SDL_Color gameUITextColor = {200, 200, 200};
    static constexpr SDL_Color playerHurtTextColor = {245, 78, 0};
    static constexpr SDL_Color enemyHurtTextColor = {150, 150, 150};
private:
    SDL_Renderer* renderer;
    bar* playerHPBar;
    button* escButton;
    button* menuButton;
    button* resumeButton;

    void openESC(bool open);
    void backToMenu();
    bool openingESC;
};
