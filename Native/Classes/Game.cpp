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

#include "Game.h"

USING_NS_CC;
    

/**********************
 *** GAME FUNCTIONS ***
 **********************/

void Game::aiMove(float dt) {
    State *s                    =   State::getShared();
    Logic::getShared()->aiMove();

    s->state                    =   GameStateP1Move;
    s->tiles[s->aiTileX][s->aiTileY] = TileStateO;
    board->drawOAt(Point(s->aiTileX, s->aiTileY));

    CCLog("AI Moved at %d %d", s->aiTileX, s->aiTileY);

    Logic::getShared()->calculateScore();
    ui->updateUI();

    if (s->highlightTiles->count() > 0) {
        s->highlightTiles->retain();
        board->scheduleOnce(schedule_selector(Board::strikeOutTiles), 1);
    }

}



/****************************
 *** BASE CLASS FUNCTIONS ***
 ****************************/

void Game::onEnter() {
    Layer::onEnter();

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Game::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(Game::onTouchEnded, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void Game::onExit() {
    Layer::onExit();

}

void Game::update(float dt) {

}

bool Game::onTouchBegan(Touch* touch, Event* event) { 
    return                          true;
}

void Game::onTouchEnded(Touch* touch, Event* event) {
    State *s                    =   State::getShared();
    auto location               =   touch->getLocation();

    auto tile                   =   board->convertScreenPixelToTile(location);

    if (tile.x != -1) {
        if (s->tiles[(int)tile.x][(int)tile.y] == TileStateNone) {
            s->selectedTileX    =   tile.x;
            s->selectedTileY    =   tile.y;
            if ( s->state == GameStateP1Move) {
                s->state        =   GameStateP2Move;
                s->tiles[(int)tile.x][(int)tile.y] = TileStateX;
                board->drawXAt(tile);
            } else {
                s->state        =   GameStateP1Move;
                s->tiles[(int)tile.x][(int)tile.y] = TileStateO;
                board->drawOAt(tile);
            }
            Logic::getShared()->calculateScore();
            ui->updateUI();
            if (s->highlightTiles->count() > 0) {
                s->highlightTiles->retain();
                board->scheduleOnce(schedule_selector(Board::strikeOutTiles), 1);
            }

            s->printTilesState();

            if (true) {
                this->scheduleOnce(schedule_selector(Game::aiMove), 2);
            }
        }
    }

}

void Game::menuCloseCallback(Object* pSender) {
    board->removeFromParentAndCleanup(true);
    board                       =   Board::create();
    board->setPosition(Point(0, 0));
    this->addChild(board);
}

// on "init" you need to initialize your instance
bool Game::init() {

    State                           *s;

    if ( !Layer::init() ) {
        return false;
    }

    visibleSize                 =   Director::getInstance()->getVisibleSize();
    Point origin                =   Director::getInstance()->getVisibleOrigin();
    s                           =   State::getShared();
    s->state                    =   GameStateP1Move;

    board                       =   Board::create();
    board->setPosition(Point(0, 0));
    this->addChild(board);

    ui                          =   UI::create();
    this->addChild(ui);

    this->scheduleUpdate();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    return true;
}

Game::~Game() {
}
