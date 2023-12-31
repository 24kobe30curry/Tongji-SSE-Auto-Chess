#include "HelloWorldScene.h"
#include "BackGroundLayer.h"
#include "goldenshovel_hero_design.h"

#include "ui/CocosGUI.h"

using namespace ui;

USING_NS_CC;

bool BackGroundLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //���뱳��ͼƬ
    auto mySprite = Sprite::create("fight_map_1.png");//������ͼ
    
    // ���õ�ͼ��ê��Ϊ���½�
    mySprite->setAnchorPoint(Vec2(0, 0));

    // ���õ�ͼ�Ĵ�СΪ���ڴ�С
    mySprite->setContentSize(visibleSize);

    // ���õ�ͼ��λ��Ϊ�������½�
    mySprite->setPosition(origin);

    //���뱳��ͼƬ
    auto platform1 = Sprite::create("platform.png");//����ƽ̨
    auto platform2 = Sprite::create("platform.png");//����ƽ̨

    // ���õ�ͼ�Ĵ�СΪ���ڴ�С

	platform1->setContentSize(Size(250,250));
	platform2->setContentSize(Size(250, 250));

    // ���õ�ͼ��λ��Ϊ�������½�
    platform1->setPosition(platform1_px);
    platform2->setPosition(platform2_px);

    auto jiban = Sprite::create("jiban4.png");//������ͼ
    jiban->setContentSize(Size(200,300));
    jiban->setPosition(Vec2(230, 900));

    // ���볡��
    this->addChild(mySprite, 0);
    this->addChild(platform1, 0);
    this->addChild(platform2, 0);
    this->addChild(jiban, 0);
    ///////////////////////////////

    return true;
}