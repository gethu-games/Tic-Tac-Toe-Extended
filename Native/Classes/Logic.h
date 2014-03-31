/*
Copyright 2014 Saiyasodharan (http://saiy2k.blogspot.in/)

This file is part of the open source game, Tic Tac Toe Extended (https://github.com/GethuGames/Tic-Tac-Toe-Extended)

Tic Tac Toe Extended is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Tic Tac Toe Extended is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Tic Tac Toe Extended.  If not, see <http://www.gnu.org/licenses/>.
*/

/* 
 * This class contains algorithms to find Scores and AI Moves
 * As of now, very raw brute force algorithm is employed. It should be
 * updated to more efficeint algorithms
 */

#ifndef __LOGIC_H__
#define __LOGIC_H__

#include "cocos2d.h"
#include "State.h"
#include "Config.h"
using namespace cocos2d;

class Logic {
public:

    void                            calculateScore();

    void                            aiMove();

    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    static Logic                    *getShared();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    void                            init();  
     
};

#endif // __LOGIC_H__
