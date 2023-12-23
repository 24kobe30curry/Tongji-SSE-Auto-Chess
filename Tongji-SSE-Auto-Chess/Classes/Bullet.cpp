#include "goldenshovel_hero_design.h"
#include "Bullet.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

Bullet::Bullet(MyHero* targetHero,Vec2 loc,int h,string name)
{
	//��������Ϊ��Ŀ��Ӣ�ۣ��ӵ����ɵ�λ�ã��˺���ͼƬ����
	//position = loc;//locΪ�����ӵ���Ӣ�۵�λ��
	target_hero = targetHero;//�����Ŀ��Ӣ��
	hurt = h;//�ӵ��˺���Ӣ���˺�һ��
	sprite = Sprite::create(name+".png");
	sprite->setPosition(loc);
}

bool Bullet::Hitted()
{
	//�ж��Ƿ����
	return sprite->getPositionX() == target.x&&sprite->getPositionY()==target.y;
}