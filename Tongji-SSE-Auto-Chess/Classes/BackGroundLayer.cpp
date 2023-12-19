#include "HelloWorldScene.h"
#include "BackGroundLayer.h"

USING_NS_CC;

bool BackGroundLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////
    //���뱳��ͼƬ
    auto mySprite = Sprite::create("fight_map.png");//������ͼ
    
    // ���þ���ͼƬ��ê��Ϊ���½�
    mySprite->setAnchorPoint(Vec2(0, 0));

    // ���þ���ͼƬ�Ĵ�СΪ���ڴ�С
    mySprite->setContentSize(visibleSize);

    // ���þ���ͼƬ��λ��Ϊ�������½�
    mySprite->setPosition(origin);

    // ������ͼƬ���볡��
    this->addChild(mySprite, 0);
    ///////////////////////////////

    return true;
}