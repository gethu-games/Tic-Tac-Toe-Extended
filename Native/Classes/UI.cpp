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

#include "UI.h"

USING_NS_CC;


/********************
 *** UI FUNCTIONS ***
 ********************/ 

void UI::updateUI() {

    char buffer[20];
    sprintf(buffer, "%d", s->player1Score);
    p1ScoreLabel->setString(buffer);
    sprintf(buffer, "%d", s->player2Score);
    p2ScoreLabel->setString(buffer);

}



/************************
 *** OBJECT LIFECYCLE ***
 ************************/

// on "init" you need to initialize your instance
bool UI::init() {

    if ( !Layer::init() ) {
        return false;
    }

    s                           =   State::getShared();
     
    visibleSize                 =   Director::getInstance()->getVisibleSize();

    p1ScoreLabel                =   Label::createWithBMFont("tempFont.fnt", "0");
    p1ScoreLabel->setPosition(Point(visibleSize.width * 0.2, visibleSize.height * 0.1));
    this->addChild(p1ScoreLabel);

    p2ScoreLabel                =   Label::createWithBMFont("tempFont.fnt", "0");
    p2ScoreLabel->setPosition(Point(visibleSize.width * 0.8, visibleSize.height * 0.1));
    this->addChild(p2ScoreLabel);

    return                          true;

}

UI::~UI() {
}
