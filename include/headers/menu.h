#pragma once
#include <SDL2/SDL.h>
#include "headers/text.h"
#include "headers/button.h"
#include "headers/game.h"

enum class gameScreen;
class word;
class button;
class menu{
public:
    menu(){};
    ~menu(){};
    void init(SDL_Renderer* renderer);
    void handleEvent();
    void update();
    void render();
private:
    word* titleWord;
    word* inspiredWord;
    word* creditWord;

    button* startButton;
    button* settingButton;
    button* quitButton;

    button* fullScreenButton;
    button* resolutionButton;
    button* menuButton;
    
    bool isFullScreen;
    bool openingSetting;
    gameScreen currentDPI;
    void openSetting(bool open);
    SDL_Renderer* renderer;
};