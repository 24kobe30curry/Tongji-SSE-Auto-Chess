#pragma once
#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h"
#include <string>

USING_NS_CC;

class Bullet
{
	friend class BattleLayer;
private:
	int hurt;           //�ӵ��˺�
	MyHero* target_hero;//Ŀ��Ӣ��
	Sprite* sprite;     //���þ���

	Vec2 position;      //��ǰ����
	Vec2 target;        //Ŀ������

	string picture_name;//ͼƬ����
public:
	Bullet(MyHero*,Vec2,int,string);    //���캯��
	bool ifHit();       //�ж��Ƿ����
};