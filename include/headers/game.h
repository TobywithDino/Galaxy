#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "headers/entity.h"
#include "headers/player.h"
#include "headers/enemy.h"
#include "headers/bullet.h"
#include "headers/collision.h"
#include "headers/text.h"
#include "headers/menu.h"
#include "headers/bar.h"
#include "headers/level.h"

enum class gameState{
    gaming,
    menu,
    quiting
};

enum class gameScreen{
    fullScreen,
    screen_1600x900,
    screen_1440x810,
    screen_1366x768,
    screen_1280x720,
};

class entity;
class word;
class text;
class menu;
class level;

class game{
public:
    game();
    ~game();
    void init(const char* title);
    void run();
    void quit();
    static int GameWidth;
    static int GameHeight;
    static float scale;

    static const int maxBullets = 200;
    static const int maxEnemies = 100;
    static const int maxWords = 20;
    static const int maxBars = 1;
    static entity* bulletGroup[maxBullets];
    static entity* p;
    static entity* enemyGroup[maxEnemies];
    static word* wordGroup[maxWords];
    static bar* barGroup[maxBars];

    static void pauseGame(bool pausing);
    static bool isPausing();
    static void changeGameState(gameState newState);
    static void refreshObjects(SDL_Renderer* renderer);
    static void changeGameScreen(gameScreen newScreen);
    
private:
    static SDL_Window* window;
    SDL_Renderer* renderer;
    collision* collisionManager;
    text* textManager;//set textManager public to let menu call textManager's setInGameUI().
    menu* menuManager;
    static level* levelManager;
    static gameState state;
    static bool pause;
    bool isRunning;
    static const int FPS = 60;
    void render();
    void handleEvent();
    void update(float fframeTime);
};