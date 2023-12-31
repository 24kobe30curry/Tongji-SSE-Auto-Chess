#pragma once
#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h"
#include <string>

USING_NS_CC;

//�ӵ���
class Bullet
{
	friend class BattleLayer;
private:
	int hurt;           //�ӵ��˺�
	MyHero* target_hero=nullptr;    //Ŀ��Ӣ��
	MySprite* target_sprite=nullptr;//Ŀ��ССӢ��
	Sprite* sprite;     //���þ���

	int isAOE = 0;      //�ж��Ƿ�Ϊ��Χ�˺�

	Vec2 target;        //Ŀ������

	string picture_name;//ͼƬ����
public:
	Bullet(MyHero*,Vec2,int,string);      //���캯��1
	Bullet(MySprite*, Vec2, int, string); //���캯��2
	Bullet(MySprite* ,MyHero*, Vec2, int, string,int);//���캯��3
	bool Hitted();      //�ж��Ƿ񵽴�Ŀ��λ��
	bool HitHero();     //�Ƿ����Ӣ�ۣ�Ŀ��λ����Ӣ��λ���Ƿ�һ�£�
	void Boom(vector<MyHero>&);//��ը���Է�Χ��Ӣ�ۿ�Ѫ
};