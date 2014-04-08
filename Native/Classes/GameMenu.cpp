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

    this->schedule(schedule_selector(GameMenu::updateDrawMenuItems));

}

static int delay = 0;
void GameMenu::updateDrawMenuItems(float dt) {

    Color4F mask                =   {0, 0, 0, 1};
    triangle[1].y               -=  c->boardDrawSpeed; 
    triangle[2].x               +=  c->boardDrawSpeed; 
    stencil->clear();
    stencil->drawPolygon(triangle, 3, mask, 0, mask);

    delay++;

    if (delay == 5) {
        Point                       to;
        delay = 0;

        if (chalk->getTag() == 0) {
            chalk->setTag(1); 
            chalk->stopAllActions();
            to            =   triangle[1];
            to.y                -=  c->boardDrawSpeed * 9;
            chalk->runAction(MoveTo::create(0.1f * (visibleSize.height - to.y) / visibleSize.height, to));
        } else {
            chalk->setTag(0); 
            chalk->stopAllActions();
            to            =   triangle[2];
            to.x                +=  c->boardDrawSpeed * 9;
            chalk->runAction(MoveTo::create(0.1f * to.x / visibleSize.width, to));
        }

    }
    //chalk->setPosition(Point(triangle[2].x * 0.5f, (triangle[1].y + visibleSize.height) * 0.5f));

    if (triangle[1].y < -visibleSize.height) {
        this->unschedule(schedule_selector(GameMenu::updateDrawMenuItems));
        CCLog("STOP UPDATE MENU");
    }

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

    CCLog("GAME MENU :: INIT");

    if ( !Layer::init() ) {
        return false;
    }

    c                           =   Config::getShared();
    
    visibleSize                 =   Director::getInstance()->getVisibleSize();

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("boardSheet.plist");

    auto sprite                 =   Sprite::create("boardBG.jpg");
    sprite->setAnchorPoint(Point(0.5, 1));
    sprite->setPosition(Point(visibleSize.width/2, visibleSize.height));
    sprite->setScale(visibleSize.width / sprite->getContentSize().width);
    this->addChild(sprite);

    stencil                     =   DrawNode::create();
    triangle[0]                 =   Point(0, visibleSize.height); 
    triangle[1]                 =   Point(0, visibleSize.height - 1); 
    triangle[2]                 =   Point(1, visibleSize.height); 

    Color4F mask = {0, 0, 0, 1};
    stencil->drawPolygon(triangle, 3, mask, 0, mask);
    stencil->setPosition(Point(0, 0));
    
    ClippingNode *clipNode      =   ClippingNode::create();
    clipNode->setInverted(false);
    clipNode->setStencil(stencil);
    this->addChild(clipNode, 1);

    MenuItemFont::setFontName("pastel.ttf");
    MenuItemFont::setFontSize(visibleSize.height * 0.05);

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
    clipNode->addChild(menu, 1);

    batchNode                   =   SpriteBatchNode::create("boardSheet.png");
    this->addChild(batchNode, 2);

    chalk                       =   Sprite::createWithSpriteFrameName("chalk.png");
    chalk->setPosition(triangle[0]);
    batchNode->addChild(chalk);

    this->scheduleOnce(schedule_selector(GameMenu::drawMenuItems), 0.5);

    CCLog("GAME MENU :: INIT END");
    
    return true;
}

GameMenu::~GameMenu() {
}
