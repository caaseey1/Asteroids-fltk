//
//  SpaceObject.cpp
//  HW9
//
//  Created by Casey Stephens on 11/30/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include "SpaceObject.h"
#include "GameWindow.h"
#include <iostream>
using namespace std;

SpaceObject::SpaceObject(GameWindow* game, Vec2 pos, Vec2 velocity, double radius):
game(game), pos(pos), velocity(velocity), collision_radius(radius), Fl_Widget(1, 1, 0, 0) {};

Vec2 SpaceObject::getPos() const {
    return pos;
};

void SpaceObject::updatePos(){
    Vec2 window;
    
    window.x = game->w();
    window.y = game->h();
    pos+= velocity;
    pos %= window;
};

bool SpaceObject::checkCollision(SpaceObject* obj){
    int dist = Vec2::dist(pos, obj->pos);
    if (dist < (collision_radius + obj->collision_radius)) {
        return true; //collision
    }
    return false; //no collision
}

// void SpaceObject::draw(){} : defined in child classes :)
