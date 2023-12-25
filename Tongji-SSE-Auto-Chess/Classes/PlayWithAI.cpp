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

    Player[1].refresh_shop_free();

    Player[2].refresh_shop_free();
    //�ӿ���ô��
    /*
    MyHero hero1 = set_a_hero(Player[1],"Annie", Player[1].Hero_in_shop, Player[1].Hero_on_court);
    hero1.sprite->setPosition(Vec2(2000, 1000));
    Player[1].Hero_on_bench.push_back(hero1);
    MyHero hero2 = set_a_hero(Player[1], "Evelynn", Player[2].Hero_in_shop, Player[2].Hero_on_court);
    hero2.sprite->setPosition(Vec2(500, 500));
    Player[2].Hero_on_bench.push_back(hero2);*/
    //this->addChild(Player[1].Hero_on_bench[0].sprite, 2);

    BattleLayer* HeroBattle = BattleLayer::create(1, 2);
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

void PlayWithAI::AIPlayerBrain() {
    //���˻���սʱ��Ĭ������Player[0]Ϊ���ԣ�Player[1]Ϊ���
    while (Player[0].Hero_on_court.size() < Player[0].max_hero) {
        int max_pos = -1;
        int max_cost = 0;

        for (int i = 0; i < 4; i++) {
            if (Hero_list[Player[0].Hero_in_shop[i]].getcost() > max_cost && Hero_list[Player[0].Hero_in_shop[i]].getcost() < Player[0].money) {
                max_cost = Hero_list[Player[0].Hero_in_shop[i]].getcost();
                max_pos = i;
            }
        }

        if (max_pos > -1) {
            MyHero New;
            //�Ľӿ�
            //New = set_a_hero(Player[0],Player[0].Hero_in_shop[max_pos], Player[0].Hero_in_shop, Player[0].Hero_on_court);
            // �� New ���õ� Hero_on_court ��
            Player[0].make_a_random_hero();  // ���������̵�Ӣ��
        }

    }
}