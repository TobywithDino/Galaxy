#include <iostream>
#include "headers/game.h"

SDL_Window* game::window;
int game::GameWidth;
int game::GameHeight;
float game::scale;
entity* game::bulletGroup[game::maxBullets];
entity* game::p;
entity* game::enemyGroup[game::maxEnemies];
word* game::wordGroup[game::maxWords];
bar* game::barGroup[game::maxBars];
bool game::pause;
gameState game::state;
level* game::levelManager;

game::game(){
    window = nullptr;
    renderer = nullptr;
    scale = 1.8;
    collisionManager = nullptr;
    textManager = nullptr;
    menuManager = nullptr;
    pause = false;
    state = gameState::menu;
    isRunning = false;
}

game::~game(){}

void game::init(const char* title){
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GameWidth, GameHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if(window == nullptr) std::cout << "Could not create window.\n";

    SDL_GetWindowSize(window, &GameWidth, &GameHeight);
    scale = 1.8 * GameWidth/1600;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) std::cout << "Could not create renderer.\n";

    pause = false;
    state = gameState::menu;
    isRunning = true;
    
    // initialize entities
    p = new player(position(game::GameWidth/2, game::GameHeight/2), renderer);
    for(int i=0;i<maxBullets;i++) bulletGroup[i] = new bullet();
    for(int i=0;i<maxEnemies;i++) enemyGroup[i] = new enemy();
    for(int i=0;i<maxWords;i++) wordGroup[i] = new word();
    for(int i=0;i<maxBars;i++) barGroup[i] = new bar();
    // collision
    collisionManager = new collision();
    collisionManager->addColliders(&p);
    for(int i=0;i<maxBullets;i++) collisionManager->addColliders(&bulletGroup[i]);
    for(int i=0;i<maxEnemies;i++) collisionManager->addColliders(&enemyGroup[i]);
    // textManager
    textManager = new text();
    textManager->init(renderer);
    // menuManager
    menuManager = new menu();
    menuManager->init(renderer);
    // levelManager
    levelManager = new level();
    levelManager->init(renderer);
}

void game::run(){
    Uint64 lastTime = SDL_GetTicks64();
    int currentFrameTime;
    int oneFrameTime = 1000 / FPS;
    while(true){
        currentFrameTime = SDL_GetTicks64() - lastTime;
        if(currentFrameTime >= oneFrameTime){
            switch (state)
            {
            case gameState::menu:
                menuManager->handleEvent();
                menuManager->update();
                menuManager->render();
                break;
            case gameState::gaming:
                handleEvent();
                update((float)currentFrameTime / 100);              
                render();

                break;
            case gameState::quiting:
                return;
            }
            lastTime = SDL_GetTicks();
        }
    }
}

void game::quit(){
    delete p;
    for(int i=0;i<maxBullets;i++) delete bulletGroup[i];
    for(int i=0;i<maxEnemies;i++) delete enemyGroup[i];
    for(int i=0;i<maxWords;i++) delete wordGroup[i];
    for(int i=0;i<maxBars;i++) delete barGroup[i];
    delete collisionManager;
    delete textManager;
    delete menuManager;
    delete levelManager;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    std::cout << "Game Successfully Terminated.\n";
}

void game::handleEvent(){
    SDL_Event event;
    SDL_PollEvent(&event);
    if(event.type == SDL_QUIT) changeGameState(gameState::quiting);
    //handle UI input
    textManager->handleEvent(event);

    //handle player input
    p->handleEvent(event);


}

void game::render(){
    SDL_SetRenderDrawColor(renderer, 30, 30, 45, 255);
    SDL_RenderClear(renderer);
    
    //start render game
    p->render();
    for(auto& i : bulletGroup) i->render();
    for(auto& i : enemyGroup) i->render();
    for(auto& i : wordGroup) i->render();
    for(auto& i : barGroup) i->render();
    textManager->render();
    //end render game

    SDL_RenderPresent(renderer);
}

void game::update(float fframeTime){
    if(!pause){
        collisionManager->collisionUpdate();
        p->update(fframeTime);
        for(auto& i : bulletGroup) i->update(fframeTime);
        for(auto& i : enemyGroup)  i->update(fframeTime);
        for(auto& i : wordGroup) i->update(i->getPos());
        for(auto& i : barGroup) i->update(i->getPos());
        levelManager->update();
    }
    textManager->update();
}


//To initialize all entites and other objects. Should be called once before update function
void game::refreshObjects(SDL_Renderer* renderer){
    for(int i=0;i<maxBullets;i++) bulletGroup[i] = new bullet();
    for(int i=0;i<maxEnemies;i++) enemyGroup[i] = new enemy();
    for(int i=0;i<maxWords;i++) wordGroup[i] = new word();
    for(int i=0;i<maxBars;i++) barGroup[i] = new bar();
    //respawn player and enemies
    p->respawn(position(game::GameWidth/2, game::GameHeight/2));
    levelManager->init(renderer);
}

void game::changeGameState(gameState newState){
    state = newState;
}

void game::pauseGame(bool pausing){
    pause = pausing;
}

bool game::isPausing(){
    return pause;
}

void game::changeGameScreen(gameScreen newScreen){
    switch (newScreen)
    {
    case gameScreen::fullScreen:
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        SDL_GetWindowSize(window, &GameWidth, &GameHeight);
        scale = 1.8 * GameWidth/1600;
        break;
    case gameScreen::screen_1600x900:
        SDL_SetWindowFullscreen(window, 0);
        GameWidth = 1600;
        GameHeight = 900;
        scale = 1.8;
        break;
    case gameScreen::screen_1440x810:
        SDL_SetWindowFullscreen(window, 0);
        GameWidth = 1440;
        GameHeight = 810;
        scale = 1.8 * 1440/1600;
        break;
    case gameScreen::screen_1366x768:
        SDL_SetWindowFullscreen(window, 0);
        GameWidth = 1366;
        GameHeight = 768;
        scale = 1.8 * 1366/1600;
        break;
    case gameScreen::screen_1280x720:
        SDL_SetWindowFullscreen(window, 0);
        GameWidth = 1280;
        GameHeight = 720;
        scale = 1.8 * 1280/1600;
        break;
    default:
        break;
    }
    SDL_SetWindowSize(window, GameWidth, GameHeight);
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}