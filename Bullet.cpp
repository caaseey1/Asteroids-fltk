//
//  Bullet.cpp
//  HW9
//
//  Created by Casey Stephens on 12/2/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include "Bullet.h"
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <vector>
#include "GameWindow.h"
using namespace std;

Bullet::Bullet(GameWindow* game, Vec2 pos, Vec2 velocity):
SpaceObject(game, pos, velocity, 0.0) {}; //0 is current collision radius

void Bullet::updatePos(){ //overrides SpaceObject updatePos() for going out of window..
    pos = pos + velocity;
}
bool Bullet::checkOutOfBounds(){ //returns true if bullet is out of bounds of the window
    if((pos.x >= 800)||(pos.x < 0)||(pos.y >= 600)||(pos.y < 0)){
        return true;
    }
    else
        return false;
}
void Bullet::draw(){
    fl_push_matrix();
    fl_color(FL_BLUE); //color of bullet outline
    fl_translate(pos.x, pos.y);
    fl_begin_loop();
    fl_vertex(0.0,0.0);
    fl_vertex(0.0,4.0);
    fl_vertex(4.0,4.0);
    fl_vertex(4.0,0.0);
    fl_vertex(0.0, 0.0);
    fl_end_loop();
    fl_pop_matrix();
}
