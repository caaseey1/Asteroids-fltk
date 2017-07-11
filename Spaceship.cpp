//
//  Spaceship.cpp
//  HW9
//
//  Created by Casey Stephens on 12/2/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include "SpaceObject.h"
#include "Spaceship.h"
#include "GameWindow.h"
#include <iostream>
using namespace std;

const double Spaceship::max_speed = 20;
const double Spaceship::accel_rate = 1;
const double Spaceship::deccel_rate = 1;
const double Spaceship::rotation_rate = 10;
const double Spaceship::bullet_speed = 10;


Spaceship::Spaceship(GameWindow* game, Vec2 pos, Vec2 velocity):
SpaceObject(game, pos, velocity, 5.0){}

void Spaceship::updatePos(){
    if(accelerating) {
        accelerate();
    }
    else {
        if (velocity.magnitude() > deccel_rate) {
            Vec2 decel_vec = velocity;
            decel_vec.makeUnitLength();
            decel_vec *= -deccel_rate;
            velocity += decel_vec;
        }
        else {
            velocity = Vec2(0,0);
        }
        
    }
    
    if(rotating_left) {
        rotateLeft();
    }
    
    if(rotating_right) {
        rotateRight();
    }
    
    if(shooting) {
        shoot();
    }
    
    pos += velocity;
    pos %= Vec2(800, 600);

}

void Spaceship::setAccelerating(bool status){
    accelerating = status;
}

void Spaceship::setRotatingLeft(bool status){
    rotating_left = status;
}

void Spaceship::setRotatingRight(bool status){
    rotating_right = status;
}

void Spaceship::setShooting(bool status){
    shooting = status;
}

void Spaceship::accelerate() {
    if(velocity.magnitude() < max_speed || rotating_left || rotating_right) {
        Vec2 unit = Vec2::fromAngleDeg(orientation);
        unit *= accel_rate;
        Vec2 newSpeed = velocity + unit;
        if(newSpeed.magnitude() > max_speed) {
            velocity = unit * max_speed;
        } else {
            velocity += unit;
        }
    }
}

void Spaceship::rotateLeft() {
    orientation += rotation_rate;
    if(orientation > 360) {
        orientation -= 360;
    }
}

void Spaceship::rotateRight() {
    orientation -= rotation_rate;
    if(orientation < 0) {
        orientation += 360;
    }
}

void Spaceship::shoot() {
    Vec2 bullSpeed = Vec2::fromAngleDeg(orientation);
    bullSpeed *= bullet_speed;
    game->addBullet(pos, bullSpeed);
}


void Spaceship::draw(){
    //true==accelerating
    if(accelerating) {
        fl_color(FL_WHITE);
        fl_push_matrix();
        fl_translate(pos.x, pos.y);
        fl_rotate(orientation-135);
        fl_begin_loop();
        
        fl_vertex(0.0, 0.0);
        fl_vertex(25.0, 12.0);
        fl_vertex(12.0, 25.0);
        
        fl_end_loop();
        
        fl_begin_line();
        
        fl_vertex(25.0, 12.0);
        fl_vertex(33.0, 15.84);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(12.0, 25.0);
        fl_vertex(15.84, 33.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(15.00, 22.0);
        fl_vertex(25.0, 25.0);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(22.0, 15.0);
        fl_vertex(25.0, 25.0);
        
        fl_end_line();
        
        fl_pop_matrix();
    } else {
        fl_color(FL_WHITE);
        fl_push_matrix();
        fl_translate(pos.x, pos.y);
        fl_rotate(orientation-135);
        
        fl_begin_loop();
        
        fl_vertex(0.0, 0.0);
        fl_vertex(25.0, 12.0);
        fl_vertex(12.0, 25.0);
        
        fl_end_loop();
        
        fl_begin_line();
        
        fl_vertex(25.0, 12.0);
        fl_vertex(33.0, 15.84);
        
        fl_end_line();
        
        fl_begin_line();
        
        fl_vertex(12.0, 25.0);
        fl_vertex(15.84, 33.0);
        
        fl_end_line();
        
        fl_pop_matrix();
    }
}
