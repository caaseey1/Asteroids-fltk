//
//  Asteroid.cpp
//  HW9
//
//  Created by Casey Stephens on 11/30/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include "Asteroid.h"
#include <stdio.h>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <iostream>
#include <vector>
using namespace std;

Asteroid::Asteroid(GameWindow* game, Vec2 pos, Vec2 velocity):
SpaceObject(game, pos, velocity, 30) {};

void Asteroid::draw(){
    fl_push_matrix();
    fl_translate(pos.x, pos.y);
    fl_color(FL_GREEN);
    fl_begin_loop();
    fl_vertex(25,0);
    fl_vertex(40,12);
    fl_vertex(60,15);
    fl_vertex(80,20);
    fl_vertex(60,50);
    fl_vertex(40,40);
    fl_vertex(20,40);
    fl_vertex(0,20);
    fl_vertex(0,20);
    fl_end_loop();
    fl_pop_matrix();
}

