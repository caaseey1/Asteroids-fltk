//  main.cpp
//  HW9
//
//  Created by Casey Stephens on 11/30/16.
//  Copyright © 2016 CaseyStephens. All rights reserved.
//

#include <FL/Fl.H>
#include <ctime>
#include "GameWindow.h"
using namespace std;

int main() {
    srand(time(nullptr));
    
    GameWindow* game = new GameWindow(800, 600);
    return Fl::run();
}
