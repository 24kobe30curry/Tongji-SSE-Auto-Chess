#include "HelloWorldScene.h"
#include "Test_Scene_3.h"
#include <vector>
#include "goldenshovel_hero_design.h"

USING_NS_CC;
using namespace std;

Scene* Test_Scene_3::createScene()
{
    return Test_Scene_3::create();
}

bool Test_Scene_3::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    auto mySprite = Sprite::create("kunkun.png");//��������
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);
    this->addChild(mySprite, 0);

    /****************************************************************************************/
    auto grey1 = Sprite::create("grey_bar.png");
    auto grey2 = Sprite::create("grey_bar.png");
    auto red = Sprite::create("red_bar.png");
    auto blue = Sprite::create("blue_bar.png");
    grey1->setAnchorPoint(Vec2(0, 0));
    grey2->setAnchorPoint(Vec2(0, 0));
    red->setAnchorPoint(Vec2(0, 0));
    blue->setAnchorPoint(Vec2(0, 0));
    cocos2d::Size targetSize(370,37); // ����Ѫ���Ĵ�С
    grey1->setContentSize(targetSize);
    grey2->setContentSize(targetSize);
    red->setContentSize(targetSize);
    blue->setContentSize(targetSize);
    grey1->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 100));
    red->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 100));
    grey2->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 200));
    blue->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 200));
    cocos2d::Size red_targetSize(150, 37);
    cocos2d::Size blue_targetSize(270, 37);
    red->setContentSize(red_targetSize);
    blue->setContentSize(blue_targetSize);
    this->addChild(grey1);
    this->addChild(grey2);
    this->addChild(red);
    this->addChild(blue);
    /*******************************************************************************************************/

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

void Test_Scene_3::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();


    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

/**********����Ƿ���Ӣ�������ĺ���*********/
bool IsZeroHp(MyHero& hero)
{
    if (hero.gethp() == 0)
    {
        //this->removeChild...
        return 1;
    }
    else
        return 0;
}
void check_death(vector<MyHero>& my_vec,vector<MyHero>& enemy_vec)
{
    // ʹ�� remove_if + erase ��ϵķ�ʽ�Ƴ�����������Ԫ��
    my_vec.erase(std::remove_if(my_vec.begin(), my_vec.end(), IsZeroHp), my_vec.end());
    enemy_vec.erase(std::remove_if(enemy_vec.begin(), enemy_vec.end(), IsZeroHp), enemy_vec.end());
}

/**********�ӵ�����**********/
void bullet()
{

}

/**************�������϶��Ĵ���****************************/
/*
#ifndef __HERO_LAYER_H__
#define __HERO_LAYER_H__

#include "cocos2d.h"

class TestLayer : public cocos2d::Layer
{
public:
    virtual bool init();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(TestLayer);

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __TEST_LAYER_H__

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "HelloWorldScene.h"
#include "TestLayer.h"

USING_NS_CC;

enum
{
    kTagSprite = 1,
};

bool TestLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TestLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TestLayer::onTouchMoved, this);  // Added onTouchMoved
    listener->onTouchEnded = CC_CALLBACK_2(TestLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto mySprite = Sprite::create("grossini.png");
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);

    this->addChild(mySprite, 0, kTagSprite);
    ///////////////////////////////

    return true;
}

bool TestLayer::onTouchBegan(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();

    // Optional: Set sprite's position immediately to the touch location when touched
    s->setPosition(location);

    return true;
}

void TestLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->setPosition(location);
}

void TestLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto location = touch->getLocation();

    auto s = getChildByTag(kTagSprite);
    s->stopAllActions();
    s->runAction(MoveTo::create(1, Vec2(location.x, location.y)));

    float o = location.x - s->getPosition().x;
    float a = location.y - s->getPosition().y;
    float at = (float)CC_RADIANS_TO_DEGREES(atanf(o / a));

    if (a < 0)
    {
        if (o < 0)
            at = 180 + fabs(at);
        else
            at = 180 - fabs(at);
    }

    s->runAction(RotateTo::create(1, at));
}
*/


/*****************************������Ѫ���Ĵ���*************************************/
/*

 // ��������1
auto backBar1 = DrawNode::create();
backBar1->drawSolidRect(Vec2(-100, -15), Vec2(100, 15), Color4F(0.5, 0.5, 0.5, 1.0));

// ��������2
auto backBar2 = DrawNode::create();
backBar2->drawSolidRect(Vec2(-100, -15), Vec2(100, 15), Color4F(0.5, 0.5, 0.5, 1.0));

// ����Ѫ��
auto healthBar = ProgressTimer::create(Sprite::create("red_bar.png"));
healthBar->setType(ProgressTimer::Type::BAR);
healthBar->setMidpoint(Vec2(0, 0.5));
healthBar->setBarChangeRate(Vec2(1, 0));
healthBar->setPercentage(100); // ��ʼ�ٷֱ�
// ����Ѫ����С
healthBar->setScale(0.7, 0.3);

// ��������
auto manaBar = ProgressTimer::create(Sprite::create("blue_bar.png"));
manaBar->setType(ProgressTimer::Type::BAR);
manaBar->setMidpoint(Vec2(0, 0.5));
manaBar->setBarChangeRate(Vec2(1, 0));
manaBar->setPercentage(100); // ��ʼ�ٷֱ�
// ����������С
manaBar->setScale(0.7, 0.3);

// ���� ClippingNode
auto clipNode1 = ClippingNode::create();
clipNode1->setStencil(backBar1);
clipNode1->addChild(healthBar);

auto clipNode2 = ClippingNode::create();
clipNode2->setStencil(backBar2);
clipNode2->addChild(manaBar);

// ����Ѫ��λ��
clipNode1->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 10));
this->addChild(clipNode1);

// ��������λ��
clipNode2->setPosition(mySprite->getPosition() + Vec2(0, mySprite->getContentSize().height / 2 + 20));
this->addChild(clipNode2);

// ����Ѫ������������ֵ
float currentHealth = 80.0; // �滻�ɾ���ĵ�ǰ����ֵ
float currentMana = 77.0;   // �滻�ɾ���ĵ�ǰ����

healthBar->setPercentage(currentHealth);
manaBar->setPercentage(currentMana);


*/