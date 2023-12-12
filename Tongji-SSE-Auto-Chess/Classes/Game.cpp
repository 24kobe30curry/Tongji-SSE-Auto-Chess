#include "Game.h"
#include <goldenshovel_hero_design.h>

USING_NS_CC;

void PlayWith_AI()
{
    //������������myScene�������ٿ��Ǹ���
    auto myScene = Scene::create();//�����³���
    Director::getInstance()->pushScene(myScene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��������Ϸ���루����ΪmyScene��
    ////////////////
    //...
    ////////////////

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
    myScene->addChild(exitMenu, 1);
}

void PlayWith_Player()
{
    auto myScene = Scene::create();//�����³���
    Director::getInstance()->pushScene(myScene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //��������Ϸ����
    ////////////////
    //...
    ////////////////

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
    myScene->addChild(exitMenu, 1);
}

void slectMode()
{
    auto selcetMode_Scene = Scene::create();//�����³���
    Director::getInstance()->pushScene(selcetMode_Scene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //�����˵�(�ñ�ǩ����)
    //����һ��TTFConfig���������ñ�ǩ�Ĺ�ͬ����
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
    labelConfig.fontSize = 60;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;

    //�˵�����Ҫ�ı�ǩ
    auto ModeLabel_1 = Label::createWithTTF(labelConfig, "PlayWith_AI");
    auto ModeLabel_2 = Label::createWithTTF(labelConfig, "PlayWith_Player");

    // creating a Menu from a Vector of items
    Vector<MenuItem*> MenuItems;
    auto ModeItem_1 = MenuItemLabel::create(ModeLabel_1,
        [&](Ref* sender) {
            PlayWith_AI();
        });
    auto ModeItem_2 = MenuItemLabel::create(ModeLabel_2,
        [&](Ref* sender) {
            PlayWith_Player();
        });


    //���ø�����ǩ�ļ��
    const int height = ModeItem_1->getContentSize().height;
    ModeItem_1->setPosition(Vec2(origin.x, origin.y));
    ModeItem_2->setPosition(Vec2(origin.x, origin.y - height));

    MenuItems.pushBack(ModeItem_1);
    MenuItems.pushBack(ModeItem_2);

    auto ModeMenu = Menu::createWithArray(MenuItems);
    ModeMenu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 - height * 2));
    selcetMode_Scene->addChild(ModeMenu, 1);//�������˵����볡����

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
    selcetMode_Scene->addChild(exitMenu, 1);
}