#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
#include "PrepareLayer.h"
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

    Player[player1].sprite->setPosition(player1_px);
    Player[player1].sprite->retain();
    Player[player1].sprite->removeFromParentAndCleanup(false);
    this->addChild(Player[player1].sprite, 1);

    Player[player2].sprite->setPosition(player2_px);
    Player[player2].sprite->retain();
    Player[player2].sprite->removeFromParentAndCleanup(false);
    this->addChild(Player[player2].sprite, 1);

    //手动给敌方加英雄
    MyHero* newHero = set_a_hero(Player[player2], Player[player2].Hero_in_shop[0], Player[player2].Hero_in_shop, Player[player2].Hero_on_bench, this);
    newHero->location_x = 1;
    newHero->location_y = 1;
    newHero->sprite->setPosition(reverse_map_px(newHero->location_x, newHero->location_y, ENEMY));
    Player[player2].Hero_on_court.push_back(*newHero);

    MyHero* newHero1 = set_a_hero(Player[player2], Player[player2].Hero_in_shop[1], Player[player2].Hero_in_shop, Player[player2].Hero_on_bench, this);
    newHero1->location_x = 2;
    newHero1->location_y = 1;
    newHero1->sprite->setPosition(reverse_map_px(newHero1->location_x, newHero1->location_y, ENEMY));
    Player[player2].Hero_on_court.push_back(*newHero1);

    MyHero* newHero2 = set_a_hero(Player[player2], Player[player2].Hero_in_shop[2], Player[player2].Hero_in_shop, Player[player2].Hero_on_bench, this);
    newHero2->location_x = 3;
    newHero2->location_y = 0;
    newHero2->sprite->setPosition(reverse_map_px(newHero2->location_x, newHero2->location_y, ENEMY));
    Player[player2].Hero_on_court.push_back(*newHero2);

    Player[player1].copy();//将court中的英雄复制到fighting上
    Player[player2].copy();//将court中的英雄复制到fighting上

    /*====================商店部分========================*/
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
            store_display();// 初始化商店
        });
    cocos2d::Size targetSize(100, 100);
    auto menu0 = Menu::create(my_refresh_button, NULL);
    menu0->setTag(0);
    menu0->setContentSize(targetSize);
    menu0->setPosition(refresh_button);
    this->addChild(menu0);


    Player[player1].refresh_shop_free();// 刷新商店
    store_display();// 初始化商店
    /*====================商店部分结束========================*/


    //将双方的英雄加入场景中
    addHero(player1,ON_BENCH,ME);           
    addHero(player2,ON_BENCH,ENEMY);
    addHero(player1,FIGHTING,ME);
    addHero(player2,FIGHTING,ENEMY);

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

    ///////////////////////////////

    return true;
}


void BattleLayer::myupdate(float dt)
{
    /*以下为游戏中需要不断更新的东西*/

    checkBullet();        //检查子弹，并扣血
    check_death(Player[player1].Hero_fighting); //检查英雄死亡并退场
    check_death(Player[player2].Hero_fighting); //检查英雄死亡并退场
    seekAndMove(Player[player1].Hero_fighting, Player[player2].Hero_fighting);
    seekAndMove(Player[player2].Hero_fighting, Player[player1].Hero_fighting);

    //attribute_display();// 血条与蓝条的显示，先加上，接口后面处理
    //蓝条满放大招，后续加入

    if (gameOver(player1, player2)) {
        situation = GameOver;
        //OverShoot(player1,player2);
        this->unschedule(schedule_selector(BattleLayer::myupdate));
        this->unschedule(schedule_selector(BattleLayer::update_attack));
    }
    else if (gameOver(player2, player1)) {
        situation = GameOver;
        //OverShoot(player1, player2);
        this->unschedule(schedule_selector(BattleLayer::myupdate));
        this->unschedule(schedule_selector(BattleLayer::update_attack));
    }

}

void BattleLayer::update_attack(float dt)
{
    auto it = Player[player1].Hero_fighting.begin();
    while (it != Player[player1].Hero_fighting.end()) {
        if (it->current_enemy != nullptr&&it->enemyInDistance()) {
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景
            auto moveTo = MoveTo::create(it->attack_cd, b.target);//子弹飞行动作
            b.sprite->runAction(moveTo);
        }
        it++;
    }

    auto it2 = Player[player2].Hero_fighting.begin();
    while (it2 != Player[player2].Hero_fighting.end()) {
        if (it2->current_enemy != nullptr && it2->enemyInDistance()) {
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "basketball");//这里先都用篮球，后续写函数根据英雄名字寻找对应的子弹名字
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//子弹加入场景
            auto moveTo = MoveTo::create(it2->attack_cd, b.target);//子弹飞行动作
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
            it->current_enemy = nullptr;//目标丢失

        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//退场
            it = Hero_fighting.erase(it);//删除
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
        //    it->target = it->target_hero->sprite->getPosition();//更新目标英雄位置
        

        if (it->Hitted()) {//子弹射中目标位置

            if (it->target_hero != nullptr&&it->HitHero()) {//打中英雄
                it->target_hero->current_hp -= it->hurt;//扣血
                //扣血动画
            }
            if (it->target_sprite != nullptr) {//打中小小英雄
                it->target_sprite->current_hp -= it->hurt;//扣血
                //扣血动画
            }
            //子弹回收动画？
            this->removeChild(it->sprite, true);//退场
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
    if (Player[index1].Hero_fighting.empty()) {//玩家1的英雄死完了
        Player[index1].current_hp -= Player[index2].Hero_fighting.size();
        //this->unschedule(schedule_selector(BattleLayer::update_attack));
        return true;//返回true，表明本次战斗结束
    }
    return false;
}

void BattleLayer::OverShoot(int index1,int index2)
{
    auto it = Player[index2].Hero_fighting.begin();
    while (it != Player[index2].Hero_fighting.end()) {
        Bullet b(&Player[index1], Player[index2].sprite->getPosition(), 1, "basketball");
        bullet.push_back(b);
        this->addChild(b.sprite, 2);//子弹加入场景
        auto moveTo = MoveTo::create(it->attack_cd, b.target);//子弹飞行动作
        b.sprite->runAction(moveTo);
        it++;
    }
}

void BattleLayer::addHero(int player,int station,int camp)
{
    if (station == ON_BENCH) {
        CCLOG("%d",Player[player].Hero_on_bench.size());
        for (int i = 0; i < Player[player].Hero_on_bench.size(); i++) {
            if (camp == ME)
                Player[player].Hero_on_bench[i].sprite->setPosition(my_bench_px(i));
            else if (camp == ENEMY)
                Player[player].Hero_on_bench[i].sprite->setPosition(enemy_bench_px(i));
            Player[player].Hero_on_bench[i].sprite->retain();
            Player[player].Hero_on_bench[i].sprite->removeFromParentAndCleanup(false);
            this->addChild(Player[player].Hero_on_bench[i].sprite, 0);
        }
    }
    else if (station == FIGHTING) {
        for (int i = 0; i < Player[player].Hero_fighting.size(); i++) {
            //Player[player].sprite->setPosition(reverse_map_px(Player[player].Hero_fighting[i].location_x, Player[player].Hero_fighting[i].location_y, camp));

            Player[player].Hero_fighting[i].sprite->retain();
            Player[player].Hero_fighting[i].sprite->removeFromParentAndCleanup(false);
            this->addChild(Player[player].Hero_fighting[i].sprite, 0);
        }
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

/*----------------------显示部分-------------------------*/
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
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
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
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }
                // 移除商店中的卡片
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
            // 假设 set_a_hero 函数的原型是 MyHero* set_a_hero(...)
            MyHero* newHero = set_a_hero(Player[player1], Player[player1].Hero_in_shop[2], Player[player1].Hero_in_shop, Player[player1].Hero_on_bench, this);

            if (newHero) {
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
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
                // 设置位置
                if (newHero->sprite) {
                    newHero->sprite->setPosition(my_bench_px(Player[player1].Hero_on_bench.size()));

                    // 将 Sprite 添加到层中
                    this->addChild(newHero->sprite);
                    Player[player1].Hero_on_bench.push_back(*newHero);
                }

                // 移除商店中的卡片
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
void BattleLayer::attribute_display() // 血量与蓝条的展示
{
    auto mySprite = Sprite::create("kunkun.png");//创建精灵
    this->addChild(mySprite, 0);
    auto grey1 = Sprite::create("grey_bar.png");
    auto grey2 = Sprite::create("grey_bar.png");
    auto red = Sprite::create("red_bar.png");
    auto blue = Sprite::create("blue_bar.png");
    grey1->setAnchorPoint(Vec2(0, 0));
    grey2->setAnchorPoint(Vec2(0, 0));
    red->setAnchorPoint(Vec2(0, 0));
    blue->setAnchorPoint(Vec2(0, 0));
    cocos2d::Size targetSize(370, 37); // 调整血条的大小
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



