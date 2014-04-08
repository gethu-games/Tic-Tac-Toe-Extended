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

#include "Logic.h"

USING_NS_CC;

static Logic *instance = NULL;

void Logic::calculateScore() {
    bool                            isScoreMove;
    int                             p1, p2;
    int                             block;
    int                             tileArrayCount;
    PointArray                      *tileArray;
    Config                          *c;
    State                           *s;
    bool                            isHightlight;

    CCLog("LOGIC :: CALCULATE SCORE");

    c                           =   Config::getShared();
    s                           =   State::getShared();
    CCLog("LOGIC :: CALCULATE SCORE 1");
    isScoreMove                 =   false;
    p1                          =   0;
    p2                          =   0;
    CCLog("LOGIC :: CALCULATE SCORE 2");
    block                       =   c->scoreTile;
    CCLog("LOGIC :: CALCULATE SCORE 3");
    tileArray                   =   PointArray::create(8);
    CCLog("LOGIC :: CALCULATE SCORE 4");

    for (int i = 0; i < c->rowCount; i++) {
        for (int j = 0; j < c->colCount; j++) {
            int                     count;
            CCLog("%d %d", i, j);
            CCLog("Step 0");
            TileState cTile     =   s->tiles[i][j]; 

            CCLog("step 1");
            //CCLog(" --> %d", (int)cTile );

            //check if the current tile is not blank
            if (cTile != TileStateNone) {

                //count the states of cells in the next 'block' tiles in the current row
                count           =   0;
                tileArrayCount  =   0;
                isHightlight    =   false;
                CCLog("step 2");
                for (int z = j; z < j + block && z < c->colCount; z++) {
                    if(s->selectedTileX == i && s->selectedTileY == z)
                        isHightlight            =   true;
                    CCLog("step 2.1 %d", z);
                    tileArray->addControlPoint(Point(i, z));
                    CCLog("step 2.2 %d", z);
                    if (TileStateX == s->tiles[i][z])        count++;
                    else if (TileStateO == s->tiles[i][z])   count--;
                    else break;
                    CCLog("step 2.3 %d", z);
                }
                if (count == block) {
                    p1++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }
                if (count == -block) {
                    p2++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }

                //count the states of cells in the next 'block' tiles in the current column
                count           =   0;
                tileArrayCount  =   0;
                isHightlight    =   false;
                tileArray       =   PointArray::create(4);
                CCLog("step 3");
                for (int z = i; z < i + block && z < c->rowCount; z++) {
                    if(s->selectedTileX == z && s->selectedTileY == j)
                        isHightlight            =   true;
                    tileArray->addControlPoint(Point(z, j));
                    if (TileStateX == s->tiles[z][j])        count++;
                    else if (TileStateO == s->tiles[z][j])   count--;
                    else break;
                }
                if (count == block) {
                    p1++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }
                if (count == -block) {
                    p2++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }

                //count the number of 0s and 1s in the straight diagonal
                count           =   0;
                tileArrayCount  =   0;
                isHightlight    =   false;
                tileArray       =   PointArray::create(4);
                CCLog("step 4");
                for (int z = 0; z < block; z++) {
                    if(s->selectedTileX == z+i && s->selectedTileY == z+j)
                        isHightlight            =   true;
                    tileArray->addControlPoint(Point(z+i, z+j));
                    if ( z+j >= c->colCount || z+i >= c->rowCount )
                        break;
                    if (TileStateX == s->tiles[z+i][z+j])    count++;
                    else if (TileStateO == s->tiles[z+i][z+j]) count--;
                    else break;
                }
                if (count == block) {
                    p1++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }
                if (count == -block) {
                    p2++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }

                //count the number of 0s and 1s in the reverse diagonal
                count           =   0;
                tileArrayCount  =   0;
                isHightlight    =   false;
                tileArray       =   PointArray::create(4);
                CCLog("step 5");
                for (int z = 0; z < block; z++) {
                    if(s->selectedTileX == i-z && s->selectedTileY == z+j)
                        isHightlight            =   true;
                    tileArray->addControlPoint(Point(i-z, z+j));
                    if ( z+j >= c->colCount || i-z < 0)
                        break;
                    if (TileStateX == s->tiles[i-z][z+j])    count++;
                    else if (TileStateO == s->tiles[i-z][z+j]) count--;
                    else break;
                }
                if (count == block) {
                    p1++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }
                if (count == -block) {
                    p2++;
                    if(isHightlight) {
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(0));
                        s->highlightTiles->addControlPoint(tileArray->getControlPointAtIndex(tileArray->count() - 1));
                    }
                    int tileCount = tileArray->count();
                    for(int tt = tileCount - 1; tt >= 0; tt--) {
                        tileArray->removeControlPointAtIndex(tt);
                    } 
                }

            }
        }
    }

    //update the playerScore
    s->player1Score             =   p1;
    s->player2Score             =   p2;

    CCLog("p1 : %d; p2: %d", p1, p2);

}

void Logic::aiMove() {

    CCLog("LOGIC :: AI MOVE");

    Config                          *c;
    State                           *s;
    int                             **scoreTile;
    int                             weight, oldID;

    c                           =   Config::getShared();
    s                           =   State::getShared();

    scoreTile                   =   (int **)malloc(9 * sizeof(int *));
    for (int i = 0; i < 9; i++) {
        scoreTile[i]            =   (int *)malloc(9 * sizeof(int));
        for (int j = 0; j < 9; j++) {
            scoreTile[i][j]     =   0;
        }
    }

    CCLog("left to right");
    // checking consecutive tiles in current row from left to right
    for (int i = 0; i < c->rowCount; i++) {
        weight = 0;
        oldID = 0;
        for (int  j = 0; j < c->colCount; j++) {
            if(s->tiles[i][j] == 0) {
                scoreTile[i][j] += weight;
                weight = 0;
            } else if(s->tiles[i][j] == oldID) {
                weight++;
            } else if(s->tiles[i][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][j];
        }
    }

    CCLog("right to left");
    // checking consecutive tiles in current row from right to left
    for (int i = 0; i < c->rowCount; i++) {
        weight = 0;
        oldID = 0;
        for (int  j = c->colCount - 1; j >= 0; j--) {
            if(s->tiles[i][j] == 0) {
                //if (scoreTile[i][j] < weight)
                scoreTile[i][j] += weight;
                weight = 0;
            } else if(s->tiles[i][j] == oldID) {
                weight++;
            } else if(s->tiles[i][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][j];
        }
    }

    CCLog("top to bottom");
    // checking consecutive tiles in current col from top to bottom
    for (int  j = 0; j < c->colCount; j++) {
        weight = 0;
        oldID = 0;
        for (int i = 0; i < c->rowCount; i++) {
            if(s->tiles[i][j] == 0) {
                //if (scoreTile[i][j] < weight)
                scoreTile[i][j] += weight;
                weight = 0;
            } else if(s->tiles[i][j] == oldID) {
                weight++;
            } else if(s->tiles[i][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][j];
        }
    }

    CCLog("bottom to top");
    // checking consecutive tiles in current col from bottom to top
    for (int  j = 0; j < c->colCount; j++) {
        weight = 0;
        oldID = 0;
        for (int i = c->rowCount - 1; i >= 0; i--) {
            if(s->tiles[i][j] == 0) {
                //if (scoreTile[i][j] < weight)
                scoreTile[i][j] += weight;
                weight = 0;
            } else if(s->tiles[i][j] == oldID) {
                weight++;
            } else if(s->tiles[i][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][j];
        }
    }

    CCLog("top left to bottom right");
    // checking consecutive tiles in diagonal from top left to bottom right
    for (int i = 0; i < c->rowCount; i++) {
        int k = i;
        weight = 0;
        oldID = 0;
        for (int  j = 0; j < c->colCount && k < c->rowCount; j++)
        {
            if(s->tiles[k][j] == 0) {
                //if (scoreTile[k][j] < weight)
                scoreTile[k][j] += weight;
                weight = 0;
            }
            else if(s->tiles[k][j] == oldID) {
                weight++;
            }
            else if(s->tiles[k][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[k][j];
            k++;
        }
    }

    weight = 0;
    for (int j = 1; j < c->colCount; j++) {
        int k = j;
        weight = 0;
        oldID = 0;
        for (int  i = 0; i < c->rowCount && k < c->colCount; i++) {
            if(s->tiles[i][k] == 0) {
                //if (scoreTile[i][k] < weight)
                scoreTile[i][k] += weight;
                weight = 0;
            }
            else if(s->tiles[i][k] == oldID) {
                weight++;
            }
            else if(s->tiles[i][k] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][k];
            k++;
        }
    }

    CCLog("bottom right to top left");
    // checking consecutive tiles in diagonal from bottom right to top left
    weight = 0;
    for (int i = c->rowCount - 1; i >= 0; i--)
    {
        int k = i;
        weight = 0;
        oldID = 0;
        for (int  j = c->colCount - 1; j >= 0 && k >= 0; j--)
        {
            if(s->tiles[k][j] == 0) {
                //if (scoreTile[k][j] < weight)
                {
                    scoreTile[k][j] += weight;
                }
                weight = 0;
            }
            else if(s->tiles[k][j] == oldID) {
                weight++;
            }
            else if(s->tiles[k][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[k][j];
            k--;
        }
    }

    weight = 0;
    for (int j = c->colCount - 2; j >= 0; j--)
    {
        int k = j;
        weight = 0;
        oldID = 0;
        for (int  i = c->rowCount - 1; i >= 0 && k >= 0; i--)
        {
            if(s->tiles[i][k] == 0) {
                //if (scoreTile[i][k] < weight)
                {
                    scoreTile[i][k] += weight;
                }
                weight = 0;
            }
            else if(s->tiles[i][k] == oldID) {
                weight++;
            }
            else if(s->tiles[i][k] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][k];
            k--;
        }
    }

    CCLog("top right to bottom left");
    // checking consecutive tiles in diagonal from top right to bottom left
    weight = 0;
    for (int i = 0; i < c->rowCount; i++)
    {
        int k = i;
        weight = 0;
        oldID = 0;
        for (int  j = c->colCount - 1; j >= 0 && k < c->rowCount; j--)
        {
            if(s->tiles[k][j] == 0) {
                //if (scoreTile[k][j] < weight)
                    scoreTile[k][j] += weight;
                weight = 0;
            }
            else if(s->tiles[k][j] == oldID) {
                weight++;
            }
            else if(s->tiles[k][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[k][j];
            k++;
        }
    }

    weight = 0;
    for (int j = 0; j < c->colCount - 1; j++)
    {
        int k = j;
        weight = 0;
        oldID = 0;
        for (int  i = 0; i < c->rowCount && k > 0; i++)
        {
            if(s->tiles[i][k] == 0) {
                //if (scoreTile[i][k] < weight)
                    scoreTile[i][k] += weight;
                weight = 0;
            }
            else if(s->tiles[i][k] == oldID) {
                weight++;
            }
            else if(s->tiles[i][k] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][k];
            k--;
        }
    }

    CCLog("bottom left to top right");
    // checking consecutive tiles in diagonal from bottom left to top right
    weight = 0;
    for (int i = c->rowCount - 1; i >= 0; i--)
    {
        int k = i;
        weight = 0;
        oldID = 0;
        for (int  j = 0; j < c->colCount && k >= 0; j++)
        {
            if(s->tiles[k][j] == 0) {
                //if (scoreTile[k][j] < weight)
                {
                    scoreTile[k][j] += weight;
                }
                weight = 0;
            }
            else if(s->tiles[k][j] == oldID) {
                weight++;
            }
            else if(s->tiles[k][j] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[k][j];
            k--;
        }
    }

    weight = 0;
    for (int j = 0; j < c->colCount - 1; j++)
    {
        int k = j;
        weight = 0;
        oldID = 0;
        for (int  i = c->rowCount - 1; i >= 0 && k >= 0; i--)
        {
            if(s->tiles[i][k] == 0) {
                //if (scoreTile[i][k] < weight)
                {
                    scoreTile[i][k] += weight;
                }
                weight = 0;
            }
            else if(s->tiles[i][k] == oldID) {
                weight++;
            }
            else if(s->tiles[i][k] != oldID) {
                weight = 1;
            }
            oldID = s->tiles[i][k];
            k++;
        }
    }

    int maxScore = 0;
    int bestTileI = 0;
    int bestTileJ = 0;


    char buff[100] = "";

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            //CCLog("%d %d", i, j);
            sprintf(buff, "%s %d", buff, (int)scoreTile[i][j]);
        }
        CCLog("%s", buff);
        sprintf(buff, "");
    }

    //console.log('score tile');
    for (int i = 0; i < c->rowCount; i++) {
        //int str = '';
        for (int  j = 0; j < c->colCount; j++) {
            //str = str + ', ' + scoreTile[i][j];
            if (scoreTile[i][j] > maxScore) {
                maxScore = scoreTile[i][j];
                bestTileI = i;
                bestTileJ = j;
            }
        }
    }

    s->aiTileX = bestTileI;
    s->aiTileY = bestTileJ;
    s->selectedTileX = bestTileI;
    s->selectedTileY = bestTileJ;

    CCLog("Selected Tile: %d %d", bestTileI, bestTileJ);

}

/************************
 *** OBJECT LIFECYCLE ***
 ************************/

Logic *Logic::getShared() {
    if (instance == NULL) {
        instance                =   new Logic();
        instance->init();
    }
    return                          instance;
}

void Logic::init() {

}

