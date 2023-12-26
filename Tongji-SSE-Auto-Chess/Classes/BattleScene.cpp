#include "BattleScene.h"
#include "BackGroundLayer.h"
#include "BattleLayer.h"

bool BattleScene::init(int Player1,int Player2)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;    //��ǰ����±�
    player2 = Player2;    //��ǰ����±�

    //Player[player1].copy();
    //Player[player2].copy();

    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//����ͼƬ��

    BattleLayer* HeroBattle = BattleLayer::create(1, 2);
    this->addChild(HeroBattle);//ս����



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

BattleScene* BattleScene::create(int Player1,int Player2)
{
    BattleScene* ret = new (std::nothrow) BattleScene();
    if (ret && ret->init(Player1,Player2))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}