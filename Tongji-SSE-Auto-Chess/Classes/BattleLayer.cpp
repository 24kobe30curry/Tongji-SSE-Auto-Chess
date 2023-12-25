#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
#include <ui/UILayout.h>
using namespace std; 


USING_NS_CC;

bool BattleLayer::init(int Player1,int Player2)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    player1 = Player1;
    player2 = Player2;

    /*===================�������Ĵ���=======================*/
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BattleLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BattleLayer::onTouchMoved, this);  // Added onTouchMoved
    listener->onTouchEnded = CC_CALLBACK_2(BattleLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    /*====================�̵겿��========================*/
    auto my_refresh_button = MenuItemImage::create(
        "refresh_shop.png",
        "refresh_shop.png",
        [&](Ref* sender) {
            for(int i=1;i<=4;i++)
            {
                Node* node_with_tag_i = this->getChildByTag(i);
                if (node_with_tag_i) {
                    this->removeChild(node_with_tag_i, true);
                }
            }
            Player[player1].refresh_shop(this);
            store_display();// ��ʼ���̵�
        });
    cocos2d::Size targetSize(100, 100);
    auto menu0 = Menu::create(my_refresh_button, NULL);
    menu0->setTag(0);
    menu0->setContentSize(targetSize);
    menu0->setPosition(refresh_button);
    this->addChild(menu0);


    Player[player1].refresh_shop_free();// ˢ���̵�
    store_display();// ��ʼ���̵�
    /*====================�̵겿�ֽ���========================*/

    auto sprite1 = Sprite::create("Annie.png");
    sprite1->setPosition(enemy_bench_px(1));
    this->addChild(sprite1, 1);

    auto sprite2 = Sprite::create("Evelynn.png");
    sprite2->setPosition(enemy_bench_px(2));
    this->addChild(sprite2, 1);

    auto sprite3 = Sprite::create("Evelynn.png");
    sprite3->setPosition(enemy_bench_px(3));
    this->addChild(sprite3, 1);

    //��˫����Ӣ�ۼ��볡����
    addHero(Player[player1].Hero_on_bench,ON_BENCH,ME);           
    addHero(Player[player1].Hero_on_bench,ON_BENCH,ME);
    addHero(Player[player2].Hero_fighting,FIGHTING,ENEMY);
    addHero(Player[player2].Hero_fighting,FIGHTING,ENEMY);

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

    ///////////////////////////////

    return true;
}


void BattleLayer::myupdate(float dt)
{
    /*����Ϊ��Ϸ����Ҫ���ϸ��µĶ���*/

    checkBullet();        //����ӵ�������Ѫ
    check_death(Player[player1].Hero_fighting); //���Ӣ���������˳�
    check_death(Player[player2].Hero_fighting); //���Ӣ���������˳�
    seekAndMove(Player[player1].Hero_fighting, Player[player2].Hero_fighting);
    seekAndMove(Player[player2].Hero_fighting, Player[player1].Hero_fighting);

    //attribute_display();// Ѫ������������ʾ���ȼ��ϣ��ӿں��洦��
    //�������Ŵ��У���������

    //if (gameOver(player1, player2) || gameOver(player2, player1)) {
    //    //����ӦΪ�˳�����ս��������һЩ��������ʱûд
    //}
}

void BattleLayer::update_attack(float dt)
{
    auto it = Player[player1].Hero_fighting.begin();
    while (it != Player[player1].Hero_fighting.end()) {
        if (it->current_enemy != nullptr&&it->enemyInDistance()) {
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "basketball");//�����ȶ������򣬺���д��������Ӣ������Ѱ�Ҷ�Ӧ���ӵ�����
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//�ӵ����볡��
            auto moveTo = MoveTo::create(it->attack_cd, b.target);//�ӵ����ж���
            b.sprite->runAction(moveTo);
        }
        it++;
    }

    auto it2 = Player[player2].Hero_fighting.begin();
    while (it2 != Player[player2].Hero_fighting.end()) {
        if (it2->current_enemy != nullptr && it2->enemyInDistance()) {
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "basketball");//�����ȶ������򣬺���д��������Ӣ������Ѱ�Ҷ�Ӧ���ӵ�����
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//�ӵ����볡��
            auto moveTo = MoveTo::create(it2->attack_cd, b.target);//�ӵ����ж���
            b.sprite->runAction(moveTo);
        }
        it2++;
    }
}

void BattleLayer::check_death(vector<MyHero>& Hero_fighting)
{
    auto it = Hero_fighting.begin();
    while (it != Hero_fighting.end()) {
        if (it->current_enemy!=nullptr&&it->current_enemy->current_hp <= 0)
            it->current_enemy = nullptr;//Ŀ�궪ʧ

        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//�˳�
            it = Hero_fighting.erase(it);//ɾ��
        }
        else {
            ++it;
        }
    }
}

void BattleLayer::checkBullet()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {

        if (it->target_hero != nullptr && it->target_hero->current_hp <= 0)
            it->target_hero = nullptr;

        //if (it->target_hero != nullptr) 
        //    it->target = it->target_hero->sprite->getPosition();//����Ŀ��Ӣ��λ��
        

        if (it->Hitted()) {//�ӵ�����Ŀ��λ��

            if (it->target_hero != nullptr&&it->HitHero()) {//����Ӣ��
                it->target_hero->current_hp -= it->hurt;//��Ѫ
                //��Ѫ����
            }
            if (it->target_sprite != nullptr) {//����ССӢ��
                it->target_sprite->current_hp -= it->hurt;//��Ѫ
                //��Ѫ����
            }
            //�ӵ����ն�����
            this->removeChild(it->sprite, true);//�˳�
            it=bullet.erase(it);
        }
        else {
            ++it;
        }
    }

}

void BattleLayer::seekAndMove(vector<MyHero>& blue,vector<MyHero>& red)
{
    auto it = blue.begin();
    while (it != blue.end()) {
        if (it->current_enemy == nullptr&&!red.empty()) {
            it->seek_enemy(red);
            //CCLOG("seek_enemy successful");
            if (it->current_enemy != nullptr) {
                auto moveTo = MoveTo::create(2, it->current_enemy->sprite->getPosition());
                it->sprite->runAction(moveTo);
            }
        }
        if (it->current_enemy != nullptr) {
            if (it->enemyInDistance())
                it->sprite->stopAllActions();
        }
        it++;
    }
    //it->enemyInDistance()
}

bool BattleLayer::gameOver(int index1,int index2)
{
    if (Player[index1].Hero_fighting.empty()) {//���1��Ӣ��������
        auto it = Player[index2].Hero_fighting.begin();
        while(it!= Player[index2].Hero_fighting.end()){
            Bullet b(&Player[index1], Player[index1].sprite->getPosition(), 1, "basketball");
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//�ӵ����볡��
            auto moveTo = MoveTo::create(it->attack_cd, b.target);//�ӵ����ж���
            b.sprite->runAction(moveTo);
            it++;
        }
        return true;//����true����������ս������
    }
    return false;
}

void BattleLayer::addHero(vector<MyHero>& Hero,int station,int camp)
{
    for (int i = 0; i < Hero.size(); i++) {
        if (station == ON_BENCH) {
            if (camp == ME)
                Hero[i].sprite->setPosition(my_bench_px(i));
            else if (camp == ENEMY)
                Hero[i].sprite->setPosition(enemy_bench_px(i));
        }
        else if (station == FIGHTING) {
            Hero[i].sprite->setPosition(reverse_map_px(Hero[i].location_x, Hero[i].location_y, camp));
        }
        this->addChild(Hero[i].sprite, 0);
    }
}

BattleLayer* BattleLayer::create(int Player1,int Player2)
{
    BattleLayer* ret = new (std::nothrow) BattleLayer();
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


/*========================================�ص�����===========================================================*/
bool BattleLayer::onTouchBegan(Touch* touch, Event* event)
{
    // ��ȡ����������
    Vec2 touchPoint = touch->getLocation();

    // ����Ƿ�����Ӣ�ۣ��������Ӣ�۵�sprite�ǿɵ����
    for (int i = 0; i < Player[player1].Hero_on_bench.size(); i++)
    {
        Player[player1].Hero_on_bench[i].sprite->stopAllActions();
        if (Player[player1].Hero_on_bench[i].sprite->getBoundingBox().containsPoint(touchPoint))
        {
            initial_position = Player[player1].Hero_on_bench[i].sprite->getPosition();
            select_index = i;
            return true;
        }
    }
    return false;
}
void BattleLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto touchPoint = touch->getLocation();
    Player[player1].Hero_on_bench[select_index].sprite->setPosition(touchPoint);
}
void BattleLayer::onTouchEnded(Touch* touch, Event* event)
{
    auto touchPoint = touch->getLocation();

    if(ifInMap(touchPoint))
    {
        Player[player1].Hero_on_bench[select_index].location_x = reverse_x(touchPoint.x);
        Player[player1].Hero_on_bench[select_index].location_y = reverse_y(touchPoint.y);
        Player[player1].Hero_on_bench[select_index].sprite->setPosition(reverse_map_px(reverse_x(touchPoint.x),reverse_y(touchPoint.y),ME));
        Player[player1].Hero_on_court.push_back(Player[player1].Hero_on_bench[select_index]);// �ӵ�court��
        Player[player1].Hero_on_bench.erase(Player[player1].Hero_on_bench.begin() + select_index);// ��bench��ɾ��
    }
    else
    {
        Player[player1].Hero_on_bench[select_index].sprite->setPosition(initial_position);
    }
}


/*----------------------��ʾ����-------------------------*/
void BattleLayer::card_remove(int index)
{
    this->removeChildByTag(index + 1);
}
void BattleLayer::store_display()
{
    string hero1 = Player[player1].Hero_in_shop[0] + ".png";
    string hero2 = Player[player1].Hero_in_shop[1] + ".png";
    string hero3 = Player[player1].Hero_in_shop[2] + ".png";
    string hero4 = Player[player1].Hero_in_shop[3] + ".png";
    string card1 = Player[player1].Hero_in_shop[0] + "_Card.png";
    string card2 = Player[player1].Hero_in_shop[1] + "_Card.png";
    string card3 = Player[player1].Hero_in_shop[2] + "_Card.png";
    string card4 = Player[player1].Hero_in_shop[3] + "_Card.png";

    cocos2d::Size targetSize(500, 500);
    auto HeroCard1 = MenuItemImage::create(
        card1,
        card1,
        [&](Ref* sender) {
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[0], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // �Ƴ��̵��еĿ�Ƭ
                card_remove(0);
                Player[player1].Hero_in_shop[0] = "";
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
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[1], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // �Ƴ��̵��еĿ�Ƭ
                card_remove(1);
                Player[player1].Hero_in_shop[1] = "";
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
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[2], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // �Ƴ��̵��еĿ�Ƭ
                card_remove(2);
                Player[player1].Hero_in_shop[2] = "";
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
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[3], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // ����λ��
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // �� Sprite ��ӵ�����
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // �Ƴ��̵��еĿ�Ƭ
                card_remove(3);
                Player[player1].Hero_in_shop[3] = "";
            }
        });
    auto menu4 = Menu::create(HeroCard4, NULL);
    menu4->setTag(4);
    menu4->setContentSize(targetSize);
    menu4->setPosition(card_px(3));
    this->addChild(menu4);
}
void BattleLayer::attribute_display() // Ѫ����������չʾ
{
    auto mySprite = Sprite::create("kunkun.png");//��������
    this->addChild(mySprite, 0);
    auto grey1 = Sprite::create("grey_bar.png");
    auto grey2 = Sprite::create("grey_bar.png");
    auto red = Sprite::create("red_bar.png");
    auto blue = Sprite::create("blue_bar.png");
    grey1->setAnchorPoint(Vec2(0, 0));
    grey2->setAnchorPoint(Vec2(0, 0));
    red->setAnchorPoint(Vec2(0, 0));
    blue->setAnchorPoint(Vec2(0, 0));
    cocos2d::Size targetSize(370, 37); // ����Ѫ���Ĵ�С
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
}



