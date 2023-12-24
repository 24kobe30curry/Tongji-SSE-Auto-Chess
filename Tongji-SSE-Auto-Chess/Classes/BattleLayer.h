#pragma once
#ifndef __BATTLE_LAYER_H__
#define __BATTLE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"
#include "Bullet.h"

class BattleLayer : public cocos2d::Layer
{
public:
    virtual bool init(int Player1,int Player2);
    static BattleLayer* create(int Player1, int Player2);
    void BattleLayer::test();
    int player1;
    int player2;

    vector<MyHero> blueHero;     //����Ӣ�ۣ����ϣ�
    vector<MyHero> redHero;      //�췽Ӣ�ۣ����ϣ�

    void getHero(vector<MyHero>& Hero, int);
    void addHero(vector<MyHero>& Hero_fighting);

    vector<Bullet> bullet;        //�����ӵ�

    void myupdate(float dt);      //��Ϸ����Ҫʱ�̸��µĶ���
    void update_attack(float dt); //ƽA����

    void BattleLayer::check_death(vector<MyHero>& Hero_fighting);//�Ƴ�����Ӣ��
    void checkBullet();           //�ӵ����գ�Ӣ�ۿ�Ѫ
    void checkUltimate(vector<MyHero>& Hero_fighting);//�������Ŵ���
    void seekAndMove(vector<MyHero>&,vector<MyHero>&);//Ӣ�����в��ƶ�

    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    //CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  