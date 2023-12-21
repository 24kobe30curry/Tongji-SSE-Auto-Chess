#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include "Bullet.h"

class BattleLayer : public cocos2d::Layer
{
public:
    MySprite* player_red;         //�췽���
    MySprite* player_blue;        //�������
    vector<Bullet> bullet;        //�����ӵ�

    void schedule(SEL_SCHEDULE selector); //��ʱ��,��֡ˢ��
    void schedule(SEL_SCHEDULE selector,float interval); //��ʱ������interval��ˢ��
    virtual void update(float dt);        //��Ϸ����Ҫʱ�̸��µĶ���
    void update_attack(float dt); //ƽA����

    bool IsZeroHp(MyHero& hero);  //Ӣ���Ƿ�����
    void check_death(vector<MyHero>& my_vec, vector<MyHero>& enemy_vec);//�Ƴ�����Ӣ��
    void BulletMove();            //�ӵ��ƶ�
    void BulletDelete();          //�ӵ����գ�Ӣ�ۿ�Ѫ
    void HeroMove(vector<MyHero>&);//Ӣ���ƶ�

    virtual bool init();
    MyHero hero1;
    MyHero hero2;
    /*
    void Delete_death(vector<MyHero>& Hero_fighting) {
        auto it = Hero_fighting.begin();
        while (it != Hero_fighting.end()) {
            if (it->gethp() == 0) {
                this->removeChild(it->sprite, true);
                it = Hero_fighting.erase(it);
            }
            else {
                ++it;
            }
        }
    }*/
    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(BattleLayer);

    //void battle();
};

#endif // __BATTLE_LAYER_H__  