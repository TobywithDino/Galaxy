#pragma once

struct acceleration{
    acceleration(float xa, float ya){
        this->xa = xa;
        this->ya = ya;
    };
    acceleration(){};
    ~acceleration(){};
    bool operator==(acceleration b){
        if(xa != b.xa) return xa == b.xa;
        else return ya == b.ya;
    }
    acceleration operator+(acceleration b){
        return acceleration(xa+b.xa, ya+b.ya);
    }
    acceleration operator-(acceleration b){
        return acceleration(xa-b.xa, ya-b.ya);
    }

    float xa;
    float ya;
};