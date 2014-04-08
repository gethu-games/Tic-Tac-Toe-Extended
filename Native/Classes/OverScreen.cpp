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

#include "OverScreen.h"
#include "GameMenu.h"
#include "Game.h"

/***************************
 *** DRAW THE MENU ITEMS ***
 ***************************/

void OverScreen::drawMenuItems(float dt) {

}

void OverScreen::updateDrawMenuItems(float dt) {

}



/*********************
 *** MENU HANDLERS ***
 *********************/

void OverScreen::retryHandler(Object *pSender) {

    auto scene                  =   Scene::create();
    scene->addChild(Game::create());

    Director::getInstance()->replaceScene(scene);

}

void OverScreen::homeHandler(Object *pSender) {

    auto scene                  =   Scene::create();
    scene->addChild(GameMenu::create());

    Director::getInstance()->replaceScene(scene);


}

void OverScreen::fbShareHandler(Object *pSender) {

}

void OverScreen::tweetHandler(Object *pSender) {

}


/************************
 *** OBJECT LIFECYCLE ***
 ************************/

bool OverScreen::init() {

    CCLog("OVER SCREEN :: INIT");

    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize                 =   Director::getInstance()->getVisibleSize();

    MenuItemFont::setFontName("pastel.ttf");

    auto retryItem              =   MenuItemFont::create("retry",
                                                        this,
                                                        menu_selector(OverScreen::retryHandler));

    auto homeItem               =   MenuItemFont::create("home",
                                                         this,
                                                         menu_selector(OverScreen::homeHandler));

    auto fbItem                 =   MenuItemFont::create("FB",
                                                         this,
                                                         menu_selector(OverScreen::fbShareHandler));

    auto tweetItem              =   MenuItemFont::create("Tweet",
                                                         this,
                                                         menu_selector(OverScreen::tweetHandler));


    auto menu                   =   Menu::create(retryItem, homeItem, fbItem, tweetItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height * 0.05);
    this->addChild(menu, 1);

    auto sprite                 =   Sprite::create("boardBG.jpg");
    sprite->setAnchorPoint(Point(0.5, 1));
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height));
    sprite->setScale(visibleSize.width / sprite->getContentSize().width);
    this->addChild(sprite, 0);

    CCLog("OVER SCREEN :: INIT END");
    
    return true;
}

OverScreen::~OverScreen() {
}
