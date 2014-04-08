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

#ifndef __STATE_H__
#define __STATE_H__

#include "cocos2d.h"
using namespace cocos2d;

typedef enum {
    GameStateDrawBoard,
    GameStateWaitingForP1,
    GameStateP1Move,
    GameStateWaitingForP2,
    GameStateP2Move,
    GameStateWipeBoard,
    GameStateOver
} GameState;

typedef enum {
    TileStateNone,
    TileStateX,
    TileStateO
} TileState;



class State {
public:

    /*****************
     *** GAME DATA ***
     *****************/

    // current state of the game
    GameState                       state;

    // 2D array of `int`s that represents board state
    TileState                       **tiles;

    // number of Rows
    int                             rowCount;

    // number of Columns
    int                             colCount;

    // score of Player 1
    int                             player1Score;

    // score of Player 2
    int                             player2Score;

    // indices of the selected tile like (3, 4), (0, 1)
    int                             selectedTileX, selectedTileY;

    // number of consecutive tiles that awards points
    int                             scoreTileLength;

    // elapsed time for player 1
    float                           player1ElapsedTime;

    // elapsed time for player 22
    float                           player2ElapsedTime;

    // tiles to cut through
    PointArray                      *highlightTiles;

    // if the game is versus AI
    bool                            isAI;

    // indices of the AI Move tile
    int                             aiTileX, aiTileY;
    


    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    static State                    *getShared();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    void                            init();  

    // reset values to default
    void                            reset();
     
    void                            printTilesState();

};

#endif // __HELLOWORLD_SCENE_H__
