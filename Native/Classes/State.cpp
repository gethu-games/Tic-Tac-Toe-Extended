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

#include "State.h"

USING_NS_CC;

static State *instance = NULL;

State *State::getShared() {
    if (instance == NULL) {
        //instance                =   State::create();
        instance                =   new State();
        instance->init();
        instance->reset();
    }
    return                          instance;
}

void State::init() {
    CCLog("STATE :: INIT 2");
    highlightTiles              =   PointArray::create(20);
    highlightTiles->retain();
    tiles                       =   (TileState **)malloc(9 * sizeof(TileState *));
    for (int i = 0; i < 9; i++) {
        tiles[i]                =   (TileState *)malloc(9 * sizeof(TileState));
    }
}

void State::reset() {
    CCLog("STATE :: RESET");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            tiles[i][j]         =   TileStateNone;
        }
        //memset(tiles[i], 0, 9 * sizeof(TileState));
    }
    CCLog("STATE :: RESET END");
}

void State::printTilesState() {

    char buff[100] = "";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            //CCLog("%d %d", i, j);
            sprintf(buff, "%s %d", buff, (int)tiles[i][j]);
        }
        CCLog("%s", buff);
        sprintf(buff, "");
    }

}

