#include "BattleScene.h"
#include "BackGroundLayer.h"
#include "BattleLayer.h"
#include "PrepareScene.h"

bool BattleScene::init(int Player1,int Player2)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;    //��ǰ����±�
    player2 = Player2;    //��ǰ����±�

    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//����ͼƬ��

    HeroBattle = BattleLayer::create(1, 2);
    this->addChild(HeroBattle);//ս����

    //schedule�жϱ���ս���Ƿ����
    this->schedule(schedule_selector(BattleScene::ifGameOver));

    //������ʾ
    static int round = 0;
    round++;
    roundLabel = Label::createWithTTF("", "fonts/arial.ttf", 60);
    roundLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - roundLabel->getContentSize().height-50));
    this->addChild(roundLabel);
    roundLabel->setString(StringUtils::format("ROUND:%d", round));

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

void BattleScene::ifGameOver(float dt)
{
    if (HeroBattle->situation == GameOver) {
        //PrepareScene* prepare = PrepareScene::create(1);//���뵽�ҵı�ս����
        //Director::getInstance()->replaceScene(prepare);
        this->unschedule(schedule_selector(BattleScene::ifGameOver));
        this->scheduleOnce(schedule_selector(BattleScene::CountDown), 5.0f);
    }
}

void BattleScene::CountDown(float dt)
{
    PrepareScene* prepare = PrepareScene::create(1);//���뵽�ҵı�ս����
    CCLOG("prepare scene has been create correctly1");
    Director::getInstance()->replaceScene(prepare);
}