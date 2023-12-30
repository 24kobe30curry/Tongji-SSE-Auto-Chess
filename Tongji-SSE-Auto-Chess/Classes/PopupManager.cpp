// PopupManager.cpp
#include "PopupManager.h"

void PopupManager::displayPopup(cocos2d::Layer* parentLayer, const std::string& displayText)
{
    // ����һ����������ʾ����ͼ��
    auto background = cocos2d::Sprite::create("Blank_pop-up.png");
    background->setPosition(2560 / 2, 1600 / 2);  // ��λ������Ϊ��Ļ����
    background->setTag(7);
    parentLayer->addChild(background);

    // ����һ����ǩ����ʾ����
    auto label = cocos2d::Label::createWithTTF(displayText, "fonts/arial.ttf", 24);
    label->setPosition(2560 / 2, 1600 / 2);  // ��λ������Ϊ��Ļ����
    label->setColor(cocos2d::Color3B::BLACK);  // ����������ɫΪ��ɫ
    parentLayer->addChild(label);

    // ����һ������¼������ڹرյ���
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // �Ƴ���ǩ
        label->removeFromParent();
        // �Ƴ�����ͼƬ
        background->removeFromParent();
        return true;
    };
    parentLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, background);
}

void PopupManager::displayPopup(cocos2d::Scene* parentScene, const std::string& displayText)
{
    // ����һ����������ʾ����ͼ��
    auto background = cocos2d::Sprite::create("Blank_pop-up.png");
    background->setPosition(2560 / 2, 1600 / 2);  // ��λ������Ϊ��Ļ����
    background->setTag(7);
    parentScene->addChild(background);

    // ����һ����ǩ����ʾ����
    auto label = cocos2d::Label::createWithTTF(displayText, "fonts/arial.ttf", 24);
    label->setPosition(2560 / 2, 1600 / 2);  // ��λ������Ϊ��Ļ����
    label->setColor(cocos2d::Color3B::BLACK);  // ����������ɫΪ��ɫ
    parentScene->addChild(label);

    // ����һ������¼������ڹرյ���
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // �Ƴ���ǩ
        label->removeFromParent();
        // �Ƴ�����ͼƬ
        background->removeFromParent();
        return true;
        };
    parentScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, background);
}
