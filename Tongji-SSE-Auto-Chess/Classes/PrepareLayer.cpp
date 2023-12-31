#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "PrepareLayer.h"
#include "GameMap.h"
#include <ui/UILayout.h>
using namespace std;

USING_NS_CC;      

bool PrepareLayer::init(int index)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player = index;

    Player[player].copy();//��hero_on_court��Ӣ�۸��Ƶ���ʱ�ռ�hero_fighting��

    //��Ӣ�ۼ��볡����
    addHero(player, ON_BENCH, ME);
    addHero(player, ON_COURT, ME);
    //��ССӢ�ۼ��볡����
    addSprite(player);


    /*===================�������Ĵ���=======================*/
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(PrepareLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(PrepareLayer::onTouchMoved, this);  // Added onTouchMoved
    listener->onTouchEnded = CC_CALLBACK_2(PrepareLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(PrepareLayer::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(PrepareLayer::onMouseUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);

    /*====================�̵겿��========================*/
    auto my_refresh_button = MenuItemImage::create(
        "refresh_shop.png",
        "refresh_shop.png",
        [&](Ref* sender) {
            for (int i = 1; i <= 4; i++)
            {
                Node* node_with_tag_i = this->getChildByTag(i);
                if (node_with_tag_i) {
                    this->removeChild(node_with_tag_i, true);
                }
            }
            Player[player].refresh_shop(this);
            store_display();// ��ʼ���̵�
        });

    cocos2d::Size targetSize(100, 100);
    auto menu0 = Menu::create(my_refresh_button, NULL);
    menu0->setTag(0);
    menu0->setContentSize(targetSize);
    menu0->setPosition(refresh_button);
    this->addChild(menu0);

    auto my_buy_exp_button = MenuItemImage::create(
        "buy_exp.png", // ���ð�ť�ı���ͼ
        "buy_exp.png",
        [&](Ref* sender) {
            if (Player[player].getmoney() < 4) {
                PopupManager::displayPopup(this, "No enough Money to buy exp");
            }
            else {
                Player[player].increaseexp(4);
                Player[player].decreasemoney(4);
                Player[player].level_up();
            }
            CCLOG("buy_exp��ť�����");
        });

    auto menu_buy_exp = Menu::create(my_buy_exp_button, nullptr);
    menu_buy_exp->setTag(0); // ���ð�ť��tag���������buy_exp��ť��tagΪ1��
    menu_buy_exp->setContentSize(targetSize);
    menu_buy_exp->setPosition(buyexp_button); // ����buy_exp��ť��λ��
    this->addChild(menu_buy_exp);
   
    Player[player].refresh_shop_free();// ˢ���̵�
    store_display();// ��ʼ���̵�

    /*====================�̵겿�ֽ���========================*/

    // ����������ʾcurrent_exp�ı�ǩ
    expLabel = Label::createWithTTF("Exp: 0", "fonts/arial.ttf", 30);
    expLabel->setPosition(Vec2(100, 300));
    this->addChild(expLabel);

    // ����������ʾcurrent_money�ı�ǩ
    moneyLabel = Label::createWithTTF("Money: 0", "fonts/arial.ttf", 30);
    moneyLabel->setPosition(Vec2(100, 250));
    this->addChild(moneyLabel);

    // ����������ʾstar_level�ı�ǩ
    levelLabel = Label::createWithTTF("Level: 0", "fonts/arial.ttf", 30);
    levelLabel->setPosition(Vec2(100, 200));
    this->addChild(levelLabel);


    //��ʱ������
    this->schedule(schedule_selector(PrepareLayer::update));

    ///////////////////////////////
    return true;
}

void PrepareLayer::addHero(int player, int station, int camp)
{
    if (station == ON_BENCH) {
        if (!Player[player].Hero_on_bench.empty()) {
            auto it = Player[player].Hero_on_bench.begin();
            for (; it != Player[player].Hero_on_bench.end(); it++) {
                if (camp == ME)
                    it->sprite->setPosition(my_bench_px(it - Player[player].Hero_on_bench.begin()));
                else if (camp == ENEMY)
                    it->sprite->setPosition(enemy_bench_px(it - Player[player].Hero_on_bench.begin()));
                it->sprite->retain();
                it->sprite->removeFromParentAndCleanup(false);
                this->addChild(it->sprite, 0);
                it->sprite->getChildByTag(RED_TAG)->setContentSize(Size(HERO_BAR_LENGTH, BAR_HEIGHT));
                it->sprite->getChildByTag(BLUE_TAG)->setContentSize(Size(HERO_BAR_LENGTH, BAR_HEIGHT));
            }
        }
    }
    else if (station == FIGHTING) {
        if (!Player[player].Hero_fighting.empty()) {
            auto it = Player[player].Hero_fighting.begin();
            for (; it != Player[player].Hero_fighting.end(); it++) {            
                it->sprite->retain();
                it->sprite->removeFromParentAndCleanup(false);
                it->sprite->setPosition(reverse_map_px(it->location_x, it->location_y, camp));
                this->addChild(it->sprite, 0);
                it->sprite->getChildByTag(RED_TAG)->setScaleX(float(it->full_hp) / float(it->current_hp));
                it->sprite->getChildByTag(BLUE_TAG)->setScaleX(float(it->needed_cooldown_round) / float(it->current_cooldown_round));
            }
        }
    }
    else if (station == ON_COURT) {
        if (!Player[player].Hero_on_court.empty()) {
            auto it = Player[player].Hero_on_court.begin();
            for (; it != Player[player].Hero_on_court.end(); it++) {               
                it->sprite->removeFromParentAndCleanup(false);
                it->sprite->setPosition(reverse_map_px(it->location_x, it->location_y, camp));
                this->addChild(it->sprite, 0);
                it->sprite->getChildByTag(RED_TAG)->setScaleX(float(it->full_hp) / float(it->current_hp));
                it->sprite->getChildByTag(BLUE_TAG)->setScaleX(float(it->needed_cooldown_round) / float(it->current_cooldown_round));
            }
        }
    }
}
void PrepareLayer::addSprite(int index)
{
    char num = index + '0';
    string picture = "Player_";
    picture += num;
    picture += ".png";
    Player[index].sprite = Sprite::create(picture);
    attribute(Player[index].sprite,SPRITE_BAR_LENGTH,MY_SPRITE);
    Player[index].sprite->setPosition(player1_px);
    Player[index].sprite->getChildByTag(RED_TAG)->setScaleX(float(Player[index].current_hp) / float(Player[index].full_hp));
    this->addChild(Player[index].sprite,1,MY_SPRITE);
}

PrepareLayer* PrepareLayer::create(int index)
{
    PrepareLayer* ret = new (std::nothrow) PrepareLayer();
    if (ret && ret->init(index))
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


/*========================================�ص�����===========================================================*/
bool PrepareLayer::onTouchBegan(Touch* touch, Event* event)
{
    // ��ȡ����������
    Vec2 touchPoint = touch->getLocation();

    // ����Ƿ�����Ӣ�ۣ��������Ӣ�۵�sprite�ǿɵ����
    if (!Player[player].Hero_on_bench.empty()) {
        for (int i = 0; i < Player[player].Hero_on_bench.size(); i++)
        {
            Player[player].Hero_on_bench[i].sprite->stopAllActions();
            if (Player[player].Hero_on_bench[i].sprite->getBoundingBox().containsPoint(touchPoint))
            {
                initial_position = Player[player].Hero_on_bench[i].sprite->getPosition();
                select_index = i;
                type_index = 0;
                return true;
            }
        }
    }
    if (!Player[player].Hero_on_court.empty()) {
        for (int i = 0; i < Player[player].Hero_on_court.size(); i++)
        {
            Player[player].Hero_on_court[i].sprite->stopAllActions();
            if (Player[player].Hero_on_court[i].sprite->getBoundingBox().containsPoint(touchPoint))
            {
                initial_position = Player[player].Hero_on_court[i].sprite->getPosition();
                select_index = i;
                type_index = 1;
                return true;
            }
        }
    }
    return false;
}
void PrepareLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto touchPoint = touch->getLocation();
    if (type_index == 0)
        Player[player].Hero_on_bench[select_index].sprite->setPosition(touchPoint);
    else if (type_index == 1)
        Player[player].Hero_on_court[select_index].sprite->setPosition(touchPoint);

    if (!this->getChildByTag(17)) {
        auto selected_background = Sprite::create("selected_background.png");
        selected_background->setTag(17);
        selected_background->setPosition(Vec2(1210, 730));
        this->addChild(selected_background);
    }
}
void PrepareLayer::onTouchEnded(Touch* touch, Event* event)
{
    this->removeChildByTag(17);

    auto touchPoint = touch->getLocation();

    if (type_index == 0)
    {
        if (ifInMap(touchPoint))
        {
            if (Player[player].getlevel() + 2 <= Player[player].Hero_on_court.size()) {
                PopupManager::displayPopup(this, "Too much Hero on court");
                Player[player].Hero_on_bench[select_index].sprite->setPosition(initial_position);
            }
            else {
                int X =  reverse_x(touchPoint.x);
                int Y =  reverse_y(touchPoint.y);
                if (Player[player].MAP[X][Y] == 0) {//��λ��δ��ռ��
                    Player[player].MAP[X][Y] = 1;
                    Player[player].Hero_on_bench[select_index].sprite->setPosition(reverse_map_px(X, Y, ME));
                    Player[player].Hero_on_bench[select_index].sprite->getChildByTag(BLUE_TAG)->setScaleX(float(Player[player].Hero_on_bench[select_index].current_cooldown_round) / float(Player[player].Hero_on_bench[select_index].needed_cooldown_round));
                    Player[player].Hero_on_court.push_back(Player[player].Hero_on_bench[select_index]);// �ӵ�court��
                    CCLOG("Unchange%d %d", Player[player].Hero_on_bench[select_index].location_x, Player[player].Hero_on_bench[select_index].location_y);
                    Player[player].Hero_on_bench.erase(Player[player].Hero_on_bench.begin() + select_index);// ��bench��ɾ��
                    Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_x = X;
                    Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_y = Y;
                    CCLOG("change%d %d", Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_x, Player[player].Hero_on_court[Player[player].Hero_on_court.size() - 1].location_y);
                }
                else
                    Player[player].Hero_on_bench[select_index].sprite->setPosition(initial_position);
            }
        }
        else
        {
            Player[player].Hero_on_bench[select_index].sprite->setPosition(initial_position);
        }
    }
    else if (type_index == 1)
    {
        int initial_X = Player[player].Hero_on_court[select_index].location_x;
        int initial_Y = Player[player].Hero_on_court[select_index].location_y;
        if (ifInMap(touchPoint)) {
            int X =  reverse_x(touchPoint.x);
            int Y =  reverse_y(touchPoint.y);
            if (Player[player].MAP[X][Y] == 0) {//��λ��δ��ռ��
                Player[player].MAP[X][Y] = 1;
                Player[player].MAP[initial_X][initial_Y] = 0;
                Player[player].Hero_on_court[select_index].sprite->setPosition(reverse_map_px(X, Y, ME));
            }
            else
                Player[player].Hero_on_court[select_index].sprite->setPosition(reverse_map_px(initial_X, initial_Y, ME));
        }
        else
            Player[player].Hero_on_court[select_index].sprite->setPosition(reverse_map_px(initial_X, initial_Y,ME));
    }


}

void PrepareLayer::onMouseDown(EventMouse* event)
{
    if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_RIGHT) {
        Vec2 mousePos = event->getLocation();
        mousePos = Director::getInstance()->convertToGL(mousePos);
        mousePos = this->convertToNodeSpace(mousePos);//ת��Ϊ��������

        if (ifInMap(mousePos)&&!ifHasHero(mousePos,Player[player]))//pjl��������һ�±궨���ĳɵ�����Ϊս������ʱ
        {
            // ��������Ҽ������¼������λ��
            auto sprite = this->getChildByTag(MY_SPRITE);
            auto moveTo = MoveTo::create(2, mousePos);
            sprite->stopAllActions();
            sprite->runAction(moveTo);
        }
        else if (!ifInMap(mousePos))//������е��Ǳ�սϯӢ�۵ĵ���ж�
        {
            if (!Player[player].Hero_on_bench.empty()) {
                for (int i = 0; i < Player[player].Hero_on_bench.size(); i++)
                {
                    Player[player].Hero_on_bench[i].sprite->stopAllActions();
                    if (Player[player].Hero_on_bench[i].sprite->getBoundingBox().containsPoint(mousePos))
                    {
                        this->removeChild(Player[player].Hero_on_bench[i].sprite);
                        Player[player].money += Player[player].Hero_on_bench[i].gold_cost;
                        Player[player].Hero_on_bench.erase(Player[player].Hero_on_bench.begin() + i);
                        i--;
                    }
                }
            }
        }
        else if (ifInMap(mousePos) && ifHasHero(mousePos, Player[player]))//������е��ǳ���Ӣ�۵ĵ���ж�
        {
            if (!Player[player].Hero_on_court.empty()) {
                for (int i = 0; i < Player[player].Hero_on_court.size(); i++)
                {
                    Player[player].Hero_on_court[i].sprite->stopAllActions();
                    if (Player[player].Hero_on_court[i].sprite->getBoundingBox().containsPoint(mousePos))
                    {
                        Player[player].MAP[Player[player].Hero_on_court[i].location_x][Player[player].Hero_on_court[i].location_y] = 0;
                        this->removeChild(Player[player].Hero_on_court[i].sprite);
                        Player[player].money += Player[player].Hero_on_court[i].gold_cost;
                        Player[player].Hero_on_court.erase(Player[player].Hero_on_court.begin() + i);
                        i--;

                    }
                }
            }
        }
    }
    else if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
    {
        Vec2 mousePos = event->getLocation();
        mousePos = Director::getInstance()->convertToGL(mousePos);
        mousePos = this->convertToNodeSpace(mousePos);//ת��Ϊ��������
        if (!ifInMap(mousePos))//������е��Ǳ�սϯӢ�۵ĵ���ж�
        {
            if (!Player[player].Hero_on_bench.empty()) {
                for (int i = 0; i < Player[player].Hero_on_bench.size(); i++)
                {
                    Player[player].Hero_on_bench[i].sprite->stopAllActions();
                    if (Player[player].Hero_on_bench[i].sprite->getBoundingBox().containsPoint(mousePos))
                    {
                        auto heroInfoLabel = cocos2d::Label::createWithTTF(
                            "Ѫ��: " + std::to_string(Player[player].Hero_on_bench[i].getcurrent_hp()) + "\n" +
                            "�Ǽ�: " + std::to_string(Player[player].Hero_on_bench[i].star_level) + "\n" +
                            "������: " + std::to_string(Player[player].Hero_on_bench[i].attack_power) + "\n" +
                            "����CD: " + std::to_string(Player[player].Hero_on_bench[i].attack_cd),
                            "fonts/arial.ttf", 24);
                         CCLOG("123");
                        // ���ñ�ǩλ�ã�������Ҫ������
                        heroInfoLabel->setPosition(Vec2(1280, 800));
                        this->addChild(heroInfoLabel);
                    }
                }
            }
        }
        else if (ifInMap(mousePos) && ifHasHero(mousePos, Player[player]))//������е��ǳ���Ӣ�۵ĵ���ж�
        {
            if (!Player[player].Hero_on_court.empty()) {
                for (int i = 0; i < Player[player].Hero_on_court.size(); i++)
                {
                    Player[player].Hero_on_court[i].sprite->stopAllActions();
                    if (Player[player].Hero_on_court[i].sprite->getBoundingBox().containsPoint(mousePos))
                    {
                        auto heroInfoLabel = cocos2d::Label::createWithTTF(
                            "Ѫ��: " + std::to_string(Player[player].Hero_on_court[i].getcurrent_hp()) + "\n" +
                            "�Ǽ�: " + std::to_string(Player[player].Hero_on_court[i].star_level) + "\n" +
                            "������: " + std::to_string(Player[player].Hero_on_court[i].attack_power) + "\n" +
                            "����CD: " + std::to_string(Player[player].Hero_on_court[i].attack_cd),
                            "fonts/arial.ttf", 24);
                        
                        // ���ñ�ǩλ�ã�������Ҫ������
                        heroInfoLabel->setPosition(Vec2(1280,800));
                        this->addChild(heroInfoLabel);
                    }
                }
            }
        }
    }
}

void PrepareLayer::onMouseUp(EventMouse* event)
{
    //wjy������������ɾ��
}




/*----------------------��ʾ����-------------------------*/
void PrepareLayer::card_remove(int index)
{
    this->removeChildByTag(index + 1);
}
void PrepareLayer::store_display()
{
    string hero1 = Player[player].Hero_in_shop[0] + ".png";
    string hero2 = Player[player].Hero_in_shop[1] + ".png";
    string hero3 = Player[player].Hero_in_shop[2] + ".png";
    string hero4 = Player[player].Hero_in_shop[3] + ".png";
    string card1 = Player[player].Hero_in_shop[0] + "_Card.png";
    string card2 = Player[player].Hero_in_shop[1] + "_Card.png";
    string card3 = Player[player].Hero_in_shop[2] + "_Card.png";
    string card4 = Player[player].Hero_in_shop[3] + "_Card.png";

    cocos2d::Size targetSize(500, 500);
    auto HeroCard1 = MenuItemImage::create(
        card1,
        card1,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[0], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }
                // �Ƴ��̵��еĿ�Ƭ
                card_remove(0);
                Player[player].Hero_in_shop[0] = "";
            }
        });
    auto menu1 = Menu::create(HeroCard1, NULL);
    menu1->setTag(1);
    menu1->setContentSize(targetSize);
    menu1->setPosition(card_px(0));
    this->addChild(menu1, 0);

    auto HeroCard2 = MenuItemImage::create(
        card2,
        card2,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[1], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }
                // �Ƴ��̵��еĿ�Ƭ
                card_remove(1);
                Player[player].Hero_in_shop[1] = "";
            }
        });
    auto menu2 = Menu::create(HeroCard2, NULL);
    menu2->setTag(2);
    menu2->setContentSize(targetSize);
    menu2->setPosition(card_px(1));
    this->addChild(menu2);

    auto HeroCard3 = MenuItemImage::create(
        card3,
        card3,
        [&](Ref* sender) {
            // ���� set_a_hero ������ԭ���� MyHero* set_a_hero(...)
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[2], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }

                // �Ƴ��̵��еĿ�Ƭ
                card_remove(2);
                Player[player].Hero_in_shop[2] = "";
            }

        });
    auto menu3 = Menu::create(HeroCard3, NULL);
    menu3->setTag(3);
    menu3->setContentSize(targetSize);
    menu3->setPosition(card_px(2));
    this->addChild(menu3);

    auto HeroCard4 = MenuItemImage::create(
        card4,
        card4,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player], Player[player].Hero_in_shop[3], Player[player].Hero_in_shop, Player[player].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player].Hero_on_bench.push_back(*newHero);
                }

                // �Ƴ��̵��еĿ�Ƭ
                card_remove(3);
                Player[player].Hero_in_shop[3] = "";
            }
        });
    auto menu4 = Menu::create(HeroCard4, NULL);
    menu4->setTag(4);
    menu4->setContentSize(targetSize);
    menu4->setPosition(card_px(3));
    this->addChild(menu4);
}
void PrepareLayer::update(float dt)
{
    // ��ȡMySprite���е���Ϣ
    int currentExp = Player[player].getexp();
    int currentMoney = Player[player].getmoney();
    int starLevel = Player[player].getlevel();

    // ���±�ǩ����
    expLabel->setString(StringUtils::format("Exp: %d", currentExp));
    moneyLabel->setString(StringUtils::format("Money: %d", currentMoney));
    levelLabel->setString(StringUtils::format("Level: %d", starLevel));
}
