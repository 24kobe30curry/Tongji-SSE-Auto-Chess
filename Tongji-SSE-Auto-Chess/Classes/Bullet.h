#pragma once
#include "HelloWorldScene.h"
#include "goldenshovel_hero_design.h"
#include <string>

USING_NS_CC;

class Bullet :public Sprite
{
private:
	int hurt;           //�ӵ��˺�
	MyHero* target_hero;//Ŀ��Ӣ��

	int location_x;     //��ǰ����
	int location_y;

	int target_x;       //Ŀ������
	int target_y;      

	string picture_name;//ͼƬ����
public:
	Bullet();           //���캯��
	bool ifHit();       //�ж��Ƿ����
	void update();
};