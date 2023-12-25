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

    int select_index; // ���ڴ洢��ǰѡ�еı�սϯ�ϵ�Ӣ�۵�����

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

    void store_display();//�̵���ʾ
    void card_remove(int index);//ѡ�еĿ�Ƭ�Ƴ�

    /*cocos2d::RefPtr<cocos2d::Sprite> backgroundRef;
    cocos2d::RefPtr<cocos2d::Label> labelRef;*/

    void error_display(const std::string& displayText);
    void error_window_close();

    void attribute_display();// Ѫ������������ʾ

    /*==============�������ص�����=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    //virtual void onEnter();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    //CREATE_FUNC(BattleLayer);
};

#endif // __BATTLE_LAYER_H__  