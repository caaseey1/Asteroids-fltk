//
//  GameWindow.cpp
//  HW9
//
//  Created by Casey Stephens on 12/1/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include "GameWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <vector>
#include <iostream>
using namespace std;

const int GameWindow::max_asteroids = 15;
const int GameWindow::spawn_interval = 1;
const double GameWindow::asteroid_speed = 2.0;


// callback function for timer
void GameWindow::timer_cb(void* ptr) {
    GameWindow* cbthis = static_cast<GameWindow*>(ptr);
    cbthis->refreshGame();
    Fl::repeat_timeout(.033, timer_cb, cbthis);
}

GameWindow::GameWindow(int w, int h) : Fl_Window(w,h), cycles_survived(0), asteroids_hit(0) {
    //begin();
    this->color(0);
    //fl_color(FL_BLACK);
    Vec2 center(400,300);
    Vec2 vel(0,0);
    ship = new Spaceship(this, center, vel);
    for (int i = 0; i < (max_asteroids/2); i++) {
        spawnAsteroid();
    }
    this->end();
    this->show();
    timer_cb(this);
    Fl::add_timeout(.0333, timer_cb, this);
}

void GameWindow::spawnAsteroid() {
    this->begin();
    Vec2 vel = Vec2::fromAngleDeg(rand() % 361);
    vel *= asteroid_speed;
    vector<Vec2> startingPoints; //vector of possible asteroid spawn points
    startingPoints.push_back(Vec2(rand()%w(), 0)); //random point on top border
    startingPoints.push_back(Vec2(0,rand()%h())); //random point on left border
    startingPoints.push_back(Vec2(w(),rand()%h())); //random point on right border
    startingPoints.push_back(Vec2(rand()%w(),h())); //random point on bottom border
    int index = rand() % 4; //random index from 0-3 to choose a random spawn edge
    Vec2 pos = startingPoints.at(index);
    asteroids.push_back(new Asteroid(this, pos, vel));
    this->end();
}

void GameWindow::addBullet(Vec2 pos, Vec2 velocity) {
    this->begin();
    bullets.push_back(new Bullet(this, pos, velocity));
    this->end();
}

void GameWindow::refreshGame() {
    updatePositions();
    checkBullets();
    checkEndGame();
    if (cycles_survived > spawn_interval && asteroids.size() < max_asteroids) {
        spawnAsteroid();
    }
    this->redraw();
    }

void GameWindow::updatePositions() {
    ship->Spaceship::updatePos();
    for (int i = 0; i < bullets.size(); i++) {
        bullets.at(i)->Bullet::updatePos();
    }
    for (int j = 0; j < asteroids.size(); j++) {
        asteroids.at(j)->SpaceObject::updatePos();
    }
}

void GameWindow::checkBullets() {
    for (int i = 0; i < bullets.size(); i++) {
        for (int j = 0; j < asteroids.size(); j++) {
            if (bullets.at(i)->Bullet::checkOutOfBounds()) {
                Fl::delete_widget(bullets.at(i));
                //bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets.at(i)), bullets.end());
                bullets.erase(bullets.begin() + i);
                break;
            }
            else if (bullets.at(i)->SpaceObject::checkCollision(asteroids.at(j))) {
                Fl::delete_widget(bullets.at(i));
                //bullets.erase(std::remove(bullets.begin(), bullets.end(), bullets.at(i)), bullets.end());
                bullets.erase(bullets.begin() + i);
                //asteroids.erase(std::remove(asteroids.begin(), asteroids.end(), asteroids.at(j)), asteroids.end());
                Fl::delete_widget(asteroids.at(j));
                asteroids.erase(asteroids.begin() + j);
                asteroids_hit += 1;
                break;
            }
        }
    }
}

void GameWindow::checkEndGame() {
    for (int j = 0; j < asteroids.size(); j++) {
        if (ship->SpaceObject::checkCollision(asteroids.at(j)) == true) {
            Fl::delete_widget(ship);
            Fl::delete_widget(asteroids.at(j));
            hide();
            cout << "Game Over!" << endl;
            cout << "You survived " << cycles_survived/300 << " seconds." << endl;
            cout << "You destroyed " << asteroids_hit << " asteroids." << endl;
        }
        else {
            cycles_survived += 1;
        }
    }
}

int GameWindow::handle(int event) {
    int key = Fl::event_key();
    switch (event) {
        case FL_KEYDOWN:
            if ( key == 32) {
                ship->setShooting(true);
                return 1;
            }
            if (key == FL_Up) {
                ship->setAccelerating(true);
                return 1;
            }
            if (key == FL_Left) {
                ship->setRotatingLeft(true);
                return 1;
            }
            if (key == FL_Right) {
                ship->setRotatingRight(true);
                return 1;
            }
            return Fl_Widget::handle(event);
        case FL_KEYUP:
            if (key == 32) {
                ship->setShooting(false);
                return 1;
            }
            if (key == FL_Up) {
                ship->setAccelerating(false);
                return 1;
            }
            if (key == FL_Left) {
                ship->setRotatingLeft(false);
                return 1;
            }
            if (key == FL_Right) {
                ship->setRotatingRight(false);
                return 1;
            }
            return Fl_Widget::handle(event);
            
        default:
            return Fl_Widget::handle(event);
    }
}

