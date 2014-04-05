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

#ifndef __GAME_MENU_H__
#define __GAME_MENU_H__

#include "cocos2d.h"
#include "Config.h"

using namespace cocos2d;

class GameMenu : public Layer {
public:

    /*************************
     *** HELPER COMPONENTS ***
     *************************/

    Config                          *c;



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

    void                            vsSystemHandler(Object *pSender);

    void                            vsHumanHandler(Object *pSender);
     
    void                            helpHandler(Object *pSender);

    void                            creditsHandler(Object *pSender);

    void                            musicToggleHandler(Object *pSender);



    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    virtual bool                    init();  

    ~GameMenu();
    
    CREATE_FUNC(GameMenu);

};

#endif // __GAME_MENU_H__ 
