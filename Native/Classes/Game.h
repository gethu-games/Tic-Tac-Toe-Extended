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

#ifndef __GAME_H__
#define __GAME_H__ 

#include "cocos2d.h"
#include "State.h"
#include "Board.h"
#include "Logic.h"
#include "UI.h"

using namespace cocos2d;

class Game : public Layer {
public:

    /*******************
     *** HELPER VARS ***
     *******************/

    Size                            visibleSize;



    /************************
     *** OTHER COMPONENTS ***
     ************************/

    Board                           *board;

    UI                              *ui;

    State                           *s;

    
    /**********************
     *** GAME FUNCTIONS ***
     **********************/

    void                            aiMove(float dt);

    void                            switchToMenu(float dt);


    /******************************
     *** GAME CALLBACK HANDLERS ***
     ******************************/

    void                            boardEraseComplete();



    /****************************
     *** BASE CLASS FUNCTIONS ***
     ****************************/

    virtual void                    onEnter();
    
    virtual void                    onExit();


    /***********************
     *** TOUCH FUNCTIONS ***
     ***********************/ 

    bool                            onTouchBegan(Touch* touch, Event* event);
    
    void                            onTouchEnded(Touch* touch, Event* event);



    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool                    init();  

    // destructor
    ~Game();
     
    // implement the "static create()" method manually
    CREATE_FUNC(Game);

    // DEBUG
    void menuCloseCallback(Object* pSender);

};

#endif // __HELLOWORLD_SCENE_H__
