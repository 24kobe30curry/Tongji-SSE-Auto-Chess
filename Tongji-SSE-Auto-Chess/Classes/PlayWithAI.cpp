#include "PlayWithAI.h"
#include "BackGroundLayer.h"
#include "BattleLayer.h"

USING_NS_CC;

Scene* PlayWithAI::createScene()
{
    return PlayWithAI::create();
}

bool PlayWithAI::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);

    /*MyHero hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    hero1.sprite->setPosition(Vec2(1400, 600));
    MyHero hero2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    hero2.sprite->setPosition(Vec2(400, 700));
    hero1.current_enemy = &hero2;
    hero2.current_enemy = &hero1;
    Player[1].Hero_fighting.push_back(hero1);
    Player[2].Hero_fighting.push_back(hero2);*/

    BattleLayer* HeroBattle = BattleLayer::create();
    this->addChild(HeroBattle);
    ///////////////////////////////

    //�˳���ǰ�����İ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//�ͷŵ�ǰ�������ٴӳ���ջ�е���ջ���ĳ���������������Ϊ��ǰ���г�����
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void PlayWithAI::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}