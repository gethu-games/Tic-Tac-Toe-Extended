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

#include "GameMenu.h"
#include "Game.h"
#include "State.h"


/***************************
 *** DRAW THE MENU ITEMS ***
 ***************************/

void GameMenu::drawMenuItems(float dt) {

}

void GameMenu::updateDrawMenuItems(float dt) {

}



/*********************
 *** MENU HANDLERS ***
 *********************/

void GameMenu::vsSystemHandler(Object *pSender) {

    State::getShared()->isAI    =   true;

    auto scene                  =   Scene::create();
    scene->addChild(Game::create());

    Director::getInstance()->replaceScene(scene);

}

void GameMenu::vsHumanHandler(Object *pSender) {

    State::getShared()->isAI    =   false;

    auto scene                  =   Scene::create();
    scene->addChild(Game::create());

    Director::getInstance()->replaceScene(scene);


}

void GameMenu::helpHandler(Object *pSender) {

}

void GameMenu::creditsHandler(Object *pSender) {

}

void GameMenu::musicToggleHandler(Object *pSender) {

}


/************************
 *** OBJECT LIFECYCLE ***
 ************************/

bool GameMenu::init() {

    if ( !Layer::init() ) {
        return false;
    }
    
    visibleSize                 =   Director::getInstance()->getVisibleSize();

    MenuItemFont::setFontName("pastel.ttf");

    auto vsHumanItem            =   MenuItemFont::create("vs Human",
                                                        this,
                                                        menu_selector(GameMenu::vsHumanHandler));

    auto vsSystemItem           =   MenuItemFont::create("vs System",
                                                         this,
                                                         menu_selector(GameMenu::vsSystemHandler));

    auto helpItem               =   MenuItemFont::create("Help",
                                                         this,
                                                         menu_selector(GameMenu::helpHandler));

    auto creditsItem            =   MenuItemFont::create("Credits",
                                                         this,
                                                         menu_selector(GameMenu::creditsHandler));


    auto menu                   =   Menu::create(vsHumanItem, vsSystemItem, helpItem, creditsItem, NULL);
    menu->alignItemsVerticallyWithPadding(visibleSize.height * 0.05);
    this->addChild(menu, 1);

    auto sprite                 =   Sprite::create("boardBG.jpg");
    sprite->setAnchorPoint(Point(0.5, 1));
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height));
    sprite->setScale(visibleSize.width / sprite->getContentSize().width);
    this->addChild(sprite, 0);
    
    return true;
}
