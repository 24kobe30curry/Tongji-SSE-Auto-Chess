#pragma once
#include "goldenshovel_hero_design.h"
#include <string>

//�̵���
class Store
{
public:
	MyHero HeroInShop[5];
	int button_x;         //��ť��x����
	int button_y;         //��ť��y����
	//MySprite smallhero; //�����ĸ�ССӢ��
	int gold_x;           //���н�ҵ���ʾλ��x
	int gold_y;           //���н�ҵ���ʾλ��y
	void flushShop();     //ˢ���̵�
	void setButton();     //����ˢ�°�ť
};

//Ӣ�ۿ�Ƭ��
class Card
{
public:
	MyHero Hero;
	string CardName;

};