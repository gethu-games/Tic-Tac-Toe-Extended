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

#ifndef __BOARD_H__
#define __BOARD_H__

#include "cocos2d.h"
#include "Config.h"
#include "State.h"

using namespace cocos2d;

class Board : public Layer {
public:

    /******************
     *** BOARD VARS ***
     ******************/

    // number of rows and columns in board
    int                             rowCount, colCount;

    // width and height of the board
    Size                            boardSpace;

    int                             vLineIndex, hLineIndex;

    float                           currentLinePercent;

    Point                           currentTileToDraw;

    Point                           strikeFrom, strikeTo;

    float                           drawSpeed = 8;

    int                             lineThickness = 1;

    Point                           offset;

    Size                            cellSize;



    /*******************
     *** HELPER VARS ***
     *******************/

    Size                            visibleSize;

    Config                          *c;

    float                           variant1, variant2;



    /************************
     *** OTHER COMPONENTS ***
     ************************/

    Sprite                          *chalk;

    Sprite                          *chalkBrush;

    RenderTexture                   *texture;



    /***********************
     *** BOARD FUNCTIONS ***
     ***********************/ 

    void                            drawBoard(float dt);

    void                            updateGridDraw(float dt);

    void                            drawXAt(Point tile);

    void                            updateXDraw(float dt);

    void                            drawOAt(Point tile);

    void                            updateODraw(float dt);

    void                            drawBrushAtPoint(Point pt, bool vertical, int density, Color3B color = Color3B::WHITE);

    void                            strikeOutTiles(float dt);

    void                            updateStrikeDraw(float dt);

    // returns tile index of touched Point
    // return {-1, -1} if touched outside the grid
    Point                           convertScreenPixelToTile(Point globalPixel);

    


    /************************
     *** OBJECT LIFECYCLE ***
     ************************/

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool                    init();  

    // destructor
    ~Board();
     
    // implement the "static create()" method manually
    CREATE_FUNC(Board);
};

#endif // __HELLOWORLD_SCENE_H__
