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

#include "Board.h"

USING_NS_CC;



/***********************
 *** BOARD FUNCTIONS ***
 ***********************/ 

void Board::drawBoard(float dt) {

    vLineIndex                  =   0;
    hLineIndex                  =   -1;
    currentLinePercent          =   1.025;
    this->schedule(schedule_selector(Board::updateGridDraw));

}

void Board::updateGridDraw(float dt) {

    if (vLineIndex != -1) {
        currentLinePercent      -=  0.01 * drawSpeed;
        if (currentLinePercent < 0.08) currentLinePercent = 0.079;
        Point to                =   Point(vLineIndex * cellSize.width, currentLinePercent * boardSpace.height);
        this->drawBrushAtPoint(to, true, 30);

        if (currentLinePercent < 0.08) {
            vLineIndex++;
            if (vLineIndex <= colCount) {
                currentLinePercent= 1.025;
            } else {
                vLineIndex      =   -1;
                hLineIndex      =   rowCount;
                currentLinePercent= -0.01;
            }
        }
    }

    if (hLineIndex != -1) {
        currentLinePercent      +=  0.01 * drawSpeed;
        if (currentLinePercent > 0.93) currentLinePercent = 0.931;
        Point to                =   Point(currentLinePercent * boardSpace.width, hLineIndex * cellSize.height);
        this->drawBrushAtPoint(to, false, 30);

        if (currentLinePercent > 0.93) {
            hLineIndex--;
            if (hLineIndex != -1) {
                currentLinePercent= -0.01;
            } else {
                this->unschedule(schedule_selector(Board::updateGridDraw));
            }
        }
    }
}

void Board::drawXAt(Point tile) {

    currentLinePercent          =   0;
    currentTileToDraw           =   tile;
    variant1                    =   std::rand() % 10 / 30.0 + 0.8;
    this->schedule(schedule_selector(Board::updateXDraw));

}

void Board::updateXDraw(float dt) {

    Point                           pt;
    currentLinePercent          +=  dt * drawSpeed / 4;

    if (currentLinePercent < 0.5)
        pt                      =   Point( (currentTileToDraw.y + 0.2) * cellSize.width + currentLinePercent * cellSize.width * 1.2,
                                           (currentTileToDraw.x + 0.8) * cellSize.height - currentLinePercent * cellSize.height * 1.2);
    else
        pt                      =   Point( (currentTileToDraw.y + 0.8) * cellSize.width - (currentLinePercent - 0.5) * cellSize.width * 1.2,
                                           (currentTileToDraw.x + 0.8) * cellSize.height - (currentLinePercent - 0.5) * cellSize.height * variant1);
    this->drawBrushAtPoint(pt, false, 1, Color3B::YELLOW);
    this->drawBrushAtPoint(pt, true, 1, Color3B::YELLOW);

    if (currentLinePercent > 1.0) {
        this->unschedule(schedule_selector(Board::updateXDraw));
    }

}

void Board::drawOAt(Point tile) {

    currentLinePercent          =   0.75;
    currentTileToDraw           =   tile;
    variant1                    =   (std::rand() % 10) / 50.0;
    this->schedule(schedule_selector(Board::updateODraw));

}

void Board::updateODraw(float dt) {

    Point                           pt, center;
    float                           r = cellSize.width * 0.3;
    currentLinePercent          +=  dt * drawSpeed / 4;

    center                      =   Point((currentTileToDraw.y + 0.5f) * cellSize.width, (currentTileToDraw.x + 0.5f) * cellSize.height);
    r                           =   cellSize.width * (0.3 - (currentLinePercent - 1.25) * variant1);
    pt                          =   Point( center.x + r * cos(-currentLinePercent * 7) , center.y + r * sin(-currentLinePercent * 7));

    this->drawBrushAtPoint(pt, false, 1, Color3B::GREEN);
    this->drawBrushAtPoint(pt, true, 1, Color3B::GREEN);

    if (currentLinePercent > 1.7) {
        this->unschedule(schedule_selector(Board::updateODraw));
    }


}


// TODO: Yet to test in different screens size and varying FPS and probably need
// to calculate the density value dynamically
void Board::drawBrushAtPoint(Point pt, bool vertical, int density, Color3B color) {

    texture->begin();
    for ( int i = 0; i < density; i++) {
        // calling multiple visit()'s of a single sprite renders only the last visit() call
        // a new Sprite is required for each instance of the brush
        // This was only in cocos2dx 3.0
        // http://www.cocos2d-x.org/forums/6/topics/43886?r=43899
        chalkBrush              =   Sprite::create("chalkBrush.png");
        chalkBrush->setColor(color);
        chalkBrush->setRotation(std::rand() % 180);
        if (vertical) {
            chalkBrush->setPosition(offset + pt + Point(0, 3 * (i - density * 0.5)));
        } else {
            chalkBrush->setPosition(offset + pt + Point(3 * (i - density * 0.5), 0));
        }
        chalkBrush->visit();
    }
    texture->end();
    chalk->setPosition(offset + pt + Point(chalk->getContentSize().width * 0.3, chalk->getContentSize().height * 0.2));

}

void Board::strikeOutTiles(float dt) {
    PointArray  *ptArray        =   State::getShared()->highlightTiles;

    for (int i = 0; i < ptArray->count(); i++) {
        CCLog("pt %d %f %f", i, ptArray->getControlPointAtIndex(i).x, ptArray->getControlPointAtIndex(i).y );
    }

    strikeFrom                  =   ptArray->getControlPointAtIndex(0);
    CCLog("from tile %f %f", strikeFrom.x, strikeFrom.y);
    strikeFrom                  =   Point((strikeFrom.y + 0.5) * cellSize.width, (strikeFrom.x + 0.5) * cellSize.height);
    CCLog("from pixel %f %f", strikeFrom.x, strikeFrom.y);

    strikeTo                    =   ptArray->getControlPointAtIndex(1);
    CCLog("to tile %f %f", strikeTo.x, strikeTo.y);
    strikeTo                    =   Point((strikeTo.y + 0.5) * cellSize.width, (strikeTo.x + 0.5) * cellSize.height);
    CCLog("to pixel %f %f", strikeTo.x, strikeTo.y);

    currentLinePercent          =   0;
    this->schedule(schedule_selector(Board::updateStrikeDraw));

    State::getShared()->highlightTiles->release();
    State::getShared()->highlightTiles = NULL;

}

void Board::updateStrikeDraw(float dt) {

    float                           dx, dy;
    Point                           pt;
    currentLinePercent          +=  dt * drawSpeed / 4;

    dx                          =   strikeTo.x - strikeFrom.x;
    dy                          =   strikeTo.y - strikeFrom.y;
    pt                          =   strikeFrom + Point(dx * currentLinePercent, dy * currentLinePercent);
    this->drawBrushAtPoint(pt, true, 3, Color3B::WHITE);
    this->drawBrushAtPoint(pt, false, 3, Color3B::WHITE);

    if (currentLinePercent > 1.0) {
        this->unschedule(schedule_selector(Board::updateStrikeDraw));
    }

}

Point Board::convertScreenPixelToTile(Point globalPixel) { Point                           tileIndex;

    CCLog("Global %f %f", globalPixel.x, globalPixel.y);

    Point localPixel            =   texture->convertToNodeSpaceAR(globalPixel);
    Point localPixelAR          =   Point(localPixel.x + visibleSize.width * 0.5, localPixel.y + visibleSize.height * 0.5);
    localPixelAR                =   localPixelAR - offset;

    CCLog("Local %f %f", localPixelAR.x, localPixelAR.y);

    tileIndex                   =   Point( floor(localPixelAR.y / cellSize.height), floor(localPixelAR.x / cellSize.width));
    CCLog("Tile %f %f", tileIndex.x, tileIndex.y);

    if (tileIndex.x < 0 || tileIndex.x > 8 || tileIndex.y < 0 || tileIndex.y > 8)
        tileIndex               =   Point(-1, -1);

    return tileIndex;

}

/************************
 *** OBJECT LIFECYCLE ***
 ************************/

// on "init" you need to initialize your instance
bool Board::init() {

    if ( !Layer::init() ) {
        return false;
    }

    c                           =   Config::getShared();
    //Director::getInstance()->getScheduler()->setTimeScale(0.05);
     
    visibleSize                 =   Director::getInstance()->getVisibleSize();
    Point origin                =   Director::getInstance()->getVisibleOrigin();
    boardSpace                  =   Size(visibleSize.width * 0.75, visibleSize.width * 0.75);
    rowCount                    =   c->rowCount;
    colCount                    =   c->colCount;
    cellSize                    =   Size(boardSpace.width / colCount, boardSpace.height / rowCount);
    offset                      =   Point(visibleSize.width * 0.12, visibleSize.height * 0.3);

    Sprite *bg                  =   Sprite::create("boardBG.jpg");
    bg->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
    bg->setScale(visibleSize.height / bg->getContentSize().height);
    this->addChild(bg);

    // BUG: scales up in y-axis when equal sizes are given for width and height
    texture                     =   RenderTexture::create(visibleSize.width, visibleSize.height);
    texture->setPosition(Point(visibleSize.width * 0.5, visibleSize.height * 0.5));
    this->addChild(texture);

    chalk                       =   Sprite::create("chalk.png");
    this->addChild(chalk);

    chalkBrush                  =   Sprite::create("chalkBrush.png");
    chalkBrush->retain();

    this->scheduleOnce(schedule_selector(Board::drawBoard), 0.5);

    return true;
}

Board::~Board() {
}
