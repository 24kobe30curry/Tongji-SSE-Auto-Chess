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
	MyHero* target_hero=nullptr;//Ŀ��Ӣ��
	MySprite* target_sprite=nullptr;//Ŀ��ССӢ��
	Sprite* sprite;     //���þ���

	Vec2 target;        //Ŀ������

	string picture_name;//ͼƬ����
public:
	Bullet(MyHero*,Vec2,int,string);      //���캯��
	Bullet(MySprite*, Vec2, int, string); //���캯��2
	bool Hitted();      //�ж��Ƿ񵽴�Ŀ��λ��
	bool HitHero();     //�Ƿ����Ӣ�ۣ�Ŀ��λ����Ӣ��λ���Ƿ�һ�£�
};