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
#include "GameMenu.h"

USING_NS_CC;
    

/**********************
 *** GAME FUNCTIONS ***
 **********************/

void Game::aiMove(float dt) {

    CCLog("GAME :: AIMOVE");

    Logic::getShared()->aiMove();

    s->state                    =   GameStateP1Move;
    s->tiles[s->aiTileX][s->aiTileY] = TileStateO;
    board->drawOAt(Point(s->aiTileX, s->aiTileY));

    CCLog("AI Moved at %d %d", s->aiTileX, s->aiTileY);

    Logic::getShared()->calculateScore();
    ui->updateUI();

    if (s->highlightTiles->count() > 0) {
        board->scheduleOnce(schedule_selector(Board::strikeOutTiles), 1);
    }

}

void Game::switchToMenu(float dt) {

    CCLog("GAME :: SWITCH TO MENU");

    auto scene                  =   Scene::create();
    scene->addChild(GameMenu::create());

    Director::getInstance()->replaceScene(scene);

}


/******************************
 *** GAME CALLBACK HANDLERS ***
 ******************************/

void Game::boardEraseComplete() {
    CCLog("GAME :: BOARD ERASE COMPLETE");
    this->switchToMenu(0.0f);
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

bool Game::onTouchBegan(Touch* touch, Event* event) { 
    return                          true;
}

void Game::onTouchEnded(Touch* touch, Event* event) {
    auto location               =   touch->getLocation();

    CCLog("Game State %d", s->state);
    CCLog("is AI %d", s->isAI);

    if (s->isAI) {
        if (s->state != GameStateWaitingForP1) {
            return;
        }
    } else {
        if (!(s->state == GameStateWaitingForP1 || s->state == GameStateWaitingForP2)) {
            return;
        }
    }

    auto tile                   =   board->convertScreenPixelToTile(location);

    if (tile.x != -1) {
        if (s->tiles[(int)tile.x][(int)tile.y] == TileStateNone) {
            CCLog("Valid Move");
            s->selectedTileX    =   tile.x;
            s->selectedTileY    =   tile.y;
            if ( s->state == GameStateWaitingForP1) {
                s->state        =   GameStateP1Move;
                s->tiles[(int)tile.x][(int)tile.y] = TileStateX;
                board->drawXAt(tile);
            } else if (s->state == GameStateWaitingForP2) {
                s->state        =   GameStateP2Move;
                s->tiles[(int)tile.x][(int)tile.y] = TileStateO;
                board->drawOAt(tile);
            }
            Logic::getShared()->calculateScore();
            ui->updateUI();
            if (s->highlightTiles->count() > 0) {
                s->highlightTiles->retain();
                board->scheduleOnce(schedule_selector(Board::strikeOutTiles), 1);
            }

            //s->printTilesState();

            if (s->isAI) {
                CCLog("scheduling AI Move");
                this->scheduleOnce(schedule_selector(Game::aiMove), 2);
            }
        }
    }

}

void Game::menuCloseCallback(Object* pSender) {

    CCLog("GAME :: MENU CLOSE CALLBACK");
    /*
    board->removeFromParentAndCleanup(true);
    board                       =   Board::create();
    board->setPosition(Point(0, 0));
    this->addChild(board);
    */

    board->eraseBoard(0.0);
    s->state                    =   GameStateWipeBoard;
    s->reset();

}

// on "init" you need to initialize your instance
bool Game::init() {

    if ( !Layer::init() ) {
        return false;
    }

    visibleSize                 =   Director::getInstance()->getVisibleSize();
    s                           =   State::getShared();
    s->reset();
    s->state                    =   GameStateDrawBoard;

    board                       =   Board::create();
    board->delegate             =   this;
    board->setPosition(Point(0, 0));
    this->addChild(board);

    CCLog("Visible Size %f %f", visibleSize.width, visibleSize.height);

    ui                          =   UI::create();
    this->addChild(ui);

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Point(visibleSize.width - closeItem->getContentSize().width/2 ,
                                closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    return true;
}

Game::~Game() {
}
