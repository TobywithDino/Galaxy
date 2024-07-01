#pragma once

struct position{
    position(float x, float y){
        this->x = x;
        this->y = y;
    };
    position(){};
    ~position(){};
    bool operator==(position b){
        if(x != b.x) return x == b.x;
        else return y == b.y;
    }
    position operator+(position b){
        return position(x+b.x, y+b.y);
    }
    position operator-(position b){
        return position(x-b.x, y-b.y);
    }
    position operator*(int t){
        return position(x*t,y*t);
    }
    position operator/(float t){
        return position(x/t,y/t);
    }
    float x;
    float y;
};