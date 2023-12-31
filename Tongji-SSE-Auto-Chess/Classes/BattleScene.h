#pragma once
#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class BattleScene : public cocos2d::Scene
{
public:
    static BattleScene* create(int Player1,int Player2);
    virtual bool init(int Player1,int Player2);

    BattleLayer* HeroBattle;//ս����

    int player1;       //����±�
    int player2;       //����±�

    Label* roundLabel;//������ʾ��ǩ

    void ifGameOver(float);//�ж�����ս���Ƿ����
    void CountDown(float dt);
};

#endif // __BATTLE_SCENE_H__
