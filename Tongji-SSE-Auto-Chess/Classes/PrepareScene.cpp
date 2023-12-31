#include "PrepareScene.h"
#include "BattleScene.h"
#include "BackGroundLayer.h"
#include "PrepareLayer.h"

USING_NS_CC;

bool PrepareScene::init(int Player)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player = Player;    //��ǰ����±�

    BackGroundLayer* Map = BackGroundLayer::create();
    this->addChild(Map);//����ͼƬ

    PrepareLayer* Prepare = PrepareLayer::create(player);
    this->addChild(Prepare);//��ս��

    this->scheduleOnce(schedule_selector(PrepareScene::goToBattle), 10.0f);

    //����ʱ��ʾ
    countdown = 10;
    countdownLabel = Label::createWithTTF("", "fonts/arial.ttf", 60);
    countdownLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - countdownLabel->getContentSize().height));
    this->addChild(countdownLabel);

    this->schedule(schedule_selector(PrepareScene::updateCountdown), 1.0f);

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

void PrepareScene::goToBattle(float dt)
{
    BattleScene* battle = BattleScene::create(1, 2);
    Director::getInstance()->replaceScene(battle);
}

void PrepareScene::updateCountdown(float dt)
{
    countdown--;

    if (countdown >= 0)
    {
        countdownLabel->setString(StringUtils::format("%d", countdown));
    }
    else
    {
        countdownLabel->setString("Go!");
        this->unschedule(schedule_selector(PrepareScene::updateCountdown));
    }
}

PrepareScene* PrepareScene::create(int Player)
{
    PrepareScene* ret = new (std::nothrow) PrepareScene();
    if (ret && ret->init(Player))
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

