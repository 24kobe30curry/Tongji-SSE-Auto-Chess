#include "HelloWorldScene.h"
#include "Test_Scene_4.h"
#include "goldenshovel_hero_design.h" 
#include "BattleLayer.h"
#include "GameMap.h"
using namespace std;

USING_NS_CC;

bool BattleLayer::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /**/
    ///////////////////////////////
    hero1 = set_a_hero("Annie", Hero_1, Hero_on_court_1);
    hero1.sprite->setPosition(Vec2(1400, 600));
    //this->addChild(hero1.sprite, 0);

    hero2 = set_a_hero("Evelynn", Hero_2, Hero_on_court_2);
    hero2.sprite->setPosition(Vec2(400, 700));
    //this->addChild(hero2.sprite, 0);

    blueHero.push_back(hero1);
    redHero.push_back(hero2);

    redHero[0].current_enemy = &blueHero[0];
    blueHero[0].current_enemy = &redHero[0];

    //this->addChild(hero1.sprite, 0);
    //this->addChild(hero2.sprite, 0);

    this->addChild(blueHero[0].sprite, 0);
    this->addChild(redHero[0].sprite, 0);
    
    //player_blue->Hero_fighting[1].current_enemy = &hero2;
    //player_red->Hero_fighting[1].current_enemy = &hero1;

    this->schedule(schedule_selector(BattleLayer::myupdate));
    this->schedule(schedule_selector(BattleLayer::update_attack), 1.0f);

    GameMap[2][3] = &hero1;
    if (GameMap[2][3] == nullptr)
    {
        CCLOG("GameMap[2][3] is nullptr");
    }
    else
    {
        CCLOG("GameMap[2][3] is not nullptr");
    }
    //new_hero.hero_attack();
    //new_hero_2.hero_attack();

    ///////////////////////////////

    return true;
}

void BattleLayer::myupdate(float dt)
{
    /*����Ϊ��Ϸ����Ҫ���ϸ��µĶ���*/

    checkBullet();                          //����ӵ�������Ѫ
    check_death(blueHero);//���Ӣ���������˳�
    check_death(redHero); //���Ӣ���������˳�

    //Ӣ�����ߣ�������д����������
    //�������Ŵ��У���������
    //��һ������Ӣ�����ֹ꣬ͣս����Ȼ�����ʤ��ʣ��Ӣ�����԰��߽��п�Ѫ
}

void BattleLayer::update_attack(float dt)
{
    auto it = blueHero.begin();
    while (it!= blueHero.end()) {
        if (it->current_enemy != NULL/*&&�жϾ���*/) {
            //it->sprite->stopAllActions();//ֹͣ�ƶ�����
            Bullet b(it->current_enemy, it->sprite->getPosition(), it->attack_power, "basketball");//�����ȶ������򣬺���д��������Ӣ������Ѱ�Ҷ�Ӧ���ӵ�����
            bullet.push_back(b);
            this->addChild(b.sprite, 2);//�ӵ����볡��

            //�����������ӣ��������Ӷ���

            auto moveTo = MoveTo::create(it->attack_cd, it->current_enemy->sprite->getPosition());//�ӵ����ж���
            b.sprite->runAction(moveTo);
        }
        it++;
    }

    auto it2 = redHero.begin();
    while (it2 != redHero.end()) {
        if (it2->current_enemy != NULL) {
            Bullet b(it2->current_enemy, it2->sprite->getPosition(), it2->attack_power, "basketball");//�����ȶ������򣬺���д��������Ӣ������Ѱ�Ҷ�Ӧ���ӵ�����
            bullet.push_back(b);
            this->addChild(b.sprite, 2);

            //�����������ӣ��������Ӷ���

            auto moveTo = MoveTo::create(it2->attack_cd, it2->current_enemy->sprite->getPosition());
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
            it->current_enemy = NULL;//Ŀ�궪ʧ

        if (it->current_hp <= 0) {
            this->removeChild(it->sprite, true);//�˳�
            it = Hero_fighting.erase(it);//ɾ��
        }
        else {
            ++it;
        }
    }
    /*
    if (hero2.current_hp <= 0)
        hero1.current_enemy = NULL;//Ŀ�궪ʧ
    if (hero2.current_hp <= 0) {
        this->removeChild(hero2.sprite, true);//�˳�
    }*/
}

void BattleLayer::checkBullet()
{
    auto it = bullet.begin();
    while (it != bullet.end()) {

        if (it->target_hero->current_hp <= 0)
            it->target_hero = NULL;

        if (it->target_hero != NULL)
            it->target = it->target_hero->sprite->getPosition();//����Ŀ��Ӣ��λ��

        if (it->Hitted()) {//�ӵ�����Ŀ��λ��

            if (it->target_hero != NULL) {
                it->target_hero->current_hp -= it->hurt;//��Ѫ
                //��Ѫ����
            }
            //�ӵ����ն�����
            this->removeChild(it->sprite, true);//�˳�
            it=bullet.erase(it);
        }
        else {
            it++;
        }
    }

}

/*
void BattleLayer::HeroMove(vector<MyHero>& vec)
{
    auto it = vec.begin();
    
    while (it != vec.end()) {
        if (it->current_enemy != NULL)
            it->seek_enemy();//û��Ŀ�������
        else//��Ŀ��ͳ����ƶ�
    }
}*/

void BattleLayer::allocate(MySprite& player1, MySprite& player2)
{
    //���
    bluePlayer = player1;
    redPlayer = player2;

    //����Ӣ�۸���
    auto it1 = player1.Hero_fighting.begin();
    for (; it1 != player1.Hero_fighting.end(); ++it1)
    {
        blueHero.push_back(*it1);
    }
    auto it2 = player2.Hero_fighting.begin();
    for (; it2 != player2.Hero_fighting.end(); ++it2)
    {
        redHero.push_back(*it2);
    }
}

