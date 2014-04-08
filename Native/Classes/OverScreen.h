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

#ifndef __OVER_SCENE_H__
#define __OVER_SCENE_H__

#include "cocos2d.h"
#include "Config.h"
#include "State.h"

using namespace cocos2d;

class OverScreen : public Layer {
public:

    /*************************
     *** HELPER COMPONENTS ***
     *************************/

    Config                          *c;

    State                           *s;



    /*******************
     *** HELPER VARS ***
     *******************/

    Size                            visibleSize;



    /***************************
     *** DRAW THE MENU ITEMS ***
     ***************************/

    void                            drawMenuItems(float dt);

    void                            updateDrawMenuItems(float dt);



    /*********************
     *** MENU HANDLERS ***
     *********************/

    void                            retryHandler(Object *pSender);

    void                            homeHandler(Object *pSender);
     
    void                            fbShareHandler(Object *pSender);

    void                            tweetHandler(Object *pSender);



    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    virtual bool                    init();  

    ~OverScreen();
    
    CREATE_FUNC(OverScreen);

};

#endif // __OVER_SCENE_H__
