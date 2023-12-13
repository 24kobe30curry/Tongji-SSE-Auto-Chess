#include "SelectModeScene.h"
#include "PlayWithAI.h"
#include "PlayWithPlayer.h"

USING_NS_CC;

Scene* SelectModeScene::createScene()
{
    return SelectModeScene::create();
}

bool SelectModeScene::init()
{
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
            Director::getInstance()->pushScene(PlayWithAI::createScene());
        });
    auto ModeItem_2 = MenuItemLabel::create(ModeLabel_2,
        [&](Ref* sender) {
            Director::getInstance()->pushScene(PlayWithPlayer::createScene());
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
    this->addChild(ModeMenu, 1);//�������˵����볡����

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

void SelectModeScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}