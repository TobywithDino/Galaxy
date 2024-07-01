#include "headers/entity.h"
#include "headers/text.h"
#include <iostream>
#include <math.h>

//just initialize.
entity::entity(){
    setPos(0,0);
    setVel(0,0);
    setAcce(0,0);
    renderer = nullptr;
    tex = nullptr;
    colType = collideType::entityCollider;
    texSize = 32;
    speed = 1;
    fullHp = 1;
    hp = fullHp;
    hpRegen = 0;
    lastHpRegenTime = SDL_GetTicks64();
    damage = 1;
    frictionSpeedRatio = 0.1;
    accelerationSpeedRatio = 0.1;
    delayHurtTime = 600;
    initCollideEntity();
    travelMap = false;
    active = false;
}

//initialize an entity to the game.
entity::entity(SDL_Renderer* renderer, entityTex texName, position pos){
    setPos(pos);
    setVel(0,0);
    setAcce(0,0);
    this->renderer = renderer;
    tex = getTexture(texName);
    colType = collideType::entityCollider;
    texSize = 32;
    speed = 1;
    fullHp = 1;
    hp = fullHp;
    hpRegen = 0;
    lastHpRegenTime = SDL_GetTicks64();
    damage = 1;
    frictionSpeedRatio = 0.1;
    accelerationSpeedRatio = 0.1;
    travelMap = false;
    active = true;
}

void entity::upgrade(int tier){
//empty
}

void entity::respawn(position pos){
//empty
}

void entity::handleEvent(SDL_Event event){
//empty
}

void entity::render(){
    if(!active) return;
    SDL_Rect dst;
    dst.w = texSize * game::scale;
    dst.h = texSize * game::scale;
    dst.x = pos.x - dst.w/2;
    dst.y = pos.y - dst.h/2;
    if(SDL_RenderCopy(renderer, tex, NULL, &dst) != 0) std::cout << "entity::render() error occur: " << SDL_GetError() << std::endl;
}

void entity::update(float fframeTime){
    if(!active) return;
    if(hp <= 0) destroy();

    int hpRegenTimeGap = 1000*(1/hpRegen);
    if(hp < fullHp && SDL_GetTicks64() - lastHpRegenTime > hpRegenTimeGap){
        hp+=1;
        if(hp>=fullHp) hp = fullHp;
        lastHpRegenTime = SDL_GetTicks64();
    }

    decelerate(fframeTime);
    // vel.xv += acce.xa * fframeTime;
    // vel.yv += acce.ya * fframeTime;
    pos.x += vel.xv * fframeTime;
    pos.y += vel.yv * fframeTime;

    /*
        too many physic implement, wait for another project to import
    */
    // if(acce.xa > 0){
    //     acce.xa -= 1 * fframeTime;
    //     if(acce.xa < 0) acce.xa = 0;
    // }else if(acce.xa < 0){
    //     acce.xa += 1 * fframeTime;
    //     if(acce.xa > 0) acce.xa = 0;
    // }
    // if(acce.ya > 0){
    //     acce.ya -= 1 * fframeTime;
    //     if(acce.ya < 0) acce.ya = 0;
    // }else if(acce.ya < 0){
    //     acce.ya += 1 * fframeTime;
    //     if(acce.ya > 0) acce.ya = 0;
    // }
    
    if(travelMap){
        if(pos.x + texSize/2*game::scale < 0) pos.x = game::GameWidth + texSize/2*game::scale;
        else if(pos.x - texSize/2*game::scale > game::GameWidth) pos.x = -texSize/2*game::scale;
        if(pos.y + texSize/2*game::scale < 0) pos.y = game::GameHeight + texSize/2*game::scale;
        else if(pos.y - texSize/2*game::scale > game::GameHeight) pos.y = -texSize/2*game::scale;
    }
}

void entity::hurtByEntity(entity* hit_e, int damage){
    bool addedToColEntity = false;
    for(auto& i : colEntity){
        if(i->isActive()){
            if(i->getEnity() == hit_e){
                if(SDL_GetTicks64() - i->getLastCollideTime() < delayHurtTime){
                    return;
                }else{
                    i->setLastCollideTime(SDL_GetTicks64());
                    addedToColEntity = true;
                }
            }
        }
    }
    if(!addedToColEntity) addCollideEntity(hit_e);
    hp -= damage;
    if(hp<=0) destroy();
}

void entity::hurtByEntity(entity* hit_e, int damage, SDL_Color color, position wordPos){
    bool addedToColEntity = false;
    for(auto& i : colEntity){
        if(i->isActive()){
            if(i->getEnity() == hit_e){
                if(SDL_GetTicks64() - i->getLastCollideTime() < delayHurtTime){
                    return;
                }else{
                    i->setLastCollideTime(SDL_GetTicks64());
                    addedToColEntity = true;
                }
            }
        }
    }
    if(!addedToColEntity){
        addCollideEntity(hit_e);
    }
    hp -= damage;
    if(hp<0) hp = 0;
    if(damage>0){
        text::creatDisappearWord(new position(wordPos), 12, std::to_string(damage), color, renderer);
        if( hit_e->getColType() == collideType::playerBulletCollider ||
            hit_e->getColType() == collideType::playerCollider)
        {
            bar::createDisappearBar(position(game::GameWidth/2, 5*game::scale), {210, 180, 180}, {110, 110, 160}, this, 2, 5, renderer);
        }
    }
}

        

void entity::decelerate(float fframeTime){
    float frictionSpeed = speed * frictionSpeedRatio;
    acceleration deceToVel;
    deceToVel = getNormalizedAcceleration(frictionSpeed, vel, velocity(0,0));
    if(vel.xv > 0){
        vel.xv += deceToVel.xa * fframeTime;
        if(vel.xv < 0) vel.xv = 0;
    }else if(vel.xv < 0){
        vel.xv += deceToVel.xa * fframeTime;
        if(vel.xv > 0) vel.xv = 0;
    }
    if(vel.yv > 0){
        vel.yv += deceToVel.ya * fframeTime;
        if(vel.yv < 0) vel.yv = 0;
    }else if(vel.yv < 0){
        vel.yv += deceToVel.ya * fframeTime;
        if(vel.yv > 0) vel.yv = 0;
    }
}

void entity::accelerate(position dir, float fframeTime){
    velocity finalVel;
    acceleration acceToVel;
    float accelerationSpeed = speed * (accelerationSpeedRatio+frictionSpeedRatio);//add friction to not interrupt acce, becasue entity get friction in update all the time.
    // if(accelerationSpeed <= frictionSpeedRatio * speed) std::cout << "Warning : entity can't move because acce <= dece\n";
    finalVel = getNormalizedVelocity(speed, position(pos.x, pos.y), position(pos.x+dir.x, pos.y+dir.y));
    acceToVel = getNormalizedAcceleration(accelerationSpeed, vel, finalVel);
    if(vel.xv > finalVel.xv){
        vel.xv += acceToVel.xa * fframeTime;
        if(vel.xv < finalVel.xv) vel.xv = finalVel.xv;
    }else if(vel.xv < finalVel.xv){
        vel.xv += acceToVel.xa * fframeTime;
        if(vel.xv > finalVel.xv) vel.xv = finalVel.xv;
    }
    if(vel.yv > finalVel.yv){
        vel.yv += acceToVel.ya * fframeTime;
        if(vel.yv < finalVel.yv) vel.yv = finalVel.yv;
    }else if(vel.yv < finalVel.yv){
        vel.yv += acceToVel.ya * fframeTime;
        if(vel.yv > finalVel.yv) vel.yv = finalVel.yv;
    }
}

acceleration entity::getNormalizedAcceleration(float normalTargetSpeed, velocity from, velocity to){
    //acceleration considerates current velocity.
    float xv = to.xv - from.xv;
    float yv = to.yv - from.yv;
    float dis = sqrt(xv*xv + yv*yv);
    if(dis == 0) return acceleration(0,0);

    xv *= normalTargetSpeed / dis;
    yv *= normalTargetSpeed / dis;
    return acceleration(xv, yv);
}

velocity entity::getNormalizedVelocity(float speed, position from, position to){
    float x = to.x - from.x;
    float y = to.y - from.y;
    float dis = sqrt(x*x + y*y);
    if(dis == 0) return velocity(0,0);

    x *= speed / dis;
    y *= speed / dis;
    return velocity(x, y);
}

SDL_Texture* entity::getTexture(entityTex texName){
    SDL_Texture* texture = nullptr;
    if(texName == entityTex::testEntityTex) texture = IMG_LoadTexture(renderer, "res/testParticle.png");
    if(texName == entityTex::playerTex) texture = IMG_LoadTexture(renderer, "res/player.png");
    if(texName == entityTex::pistolBulletTex) texture = IMG_LoadTexture(renderer, "res/pistolBullet.png");
    if(texName == entityTex::machinegunBulletTex) texture = IMG_LoadTexture(renderer, "res/machinegunBullet.png");
    if(texName == entityTex::sparkleTex) texture = IMG_LoadTexture(renderer, "res/sparkle.png");
    if(texName == entityTex::fortTex) texture = IMG_LoadTexture(renderer, "res/fort.png");
    if(texture == nullptr) std::cout << "entity::getTexture : could not load texture.\n";

    return texture;
}

float entity::getCurrentSpeed(){
    float x = vel.xv;
    float y = vel.yv;
    float speed = sqrt(x*x+y*y);
    return speed;
}

void entity::destroy(){
    if(colType == collideType::enemyCollider) level::enemyAmount--;
    active = false;
}