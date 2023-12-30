#include "goldenshovel_hero_design.h"
#include "Bullet.h"
#include "cocos2d.h"
#include <string>

USING_NS_CC;

Bullet::Bullet(MyHero* targetHero,Vec2 loc,int h,string name)
{
	//��������Ϊ��Ŀ��Ӣ�ۣ��ӵ����ɵ�λ�ã��˺���ͼƬ����

	target_hero = targetHero;//�����Ŀ��Ӣ��
	target = target_hero->sprite->getPosition();//Ŀ��λ��
	hurt = h;//�ӵ��˺���Ӣ���˺�һ��
	sprite = Sprite::create(name+".png");
	sprite->setPosition(loc);//locΪ�����ӵ���Ӣ�۵�λ��
}
Bullet::Bullet(MySprite* targetSprite, Vec2 loc, int h, string name)
{
	//��������Ϊ��Ŀ��Ӣ�ۣ��ӵ����ɵ�λ�ã��˺���ͼƬ����

	target_sprite = targetSprite;//�����Ŀ��Ӣ��
	target = target_sprite->sprite->getPosition();//Ŀ��λ��
	hurt = h;//�ӵ��˺�Ϊ1
	sprite = Sprite::create(name + ".png");
	sprite->setPosition(loc);//locΪ�����ӵ���Ӣ�۵�λ��
}

Bullet::Bullet(MySprite* targetSprite,MyHero* targetHero, Vec2 loc, int h, string name,int AOE)
{
	//��������Ϊ��Ŀ��Ӣ�ۣ��ӵ����ɵ�λ�ã��˺���ͼƬ����
	target_sprite = targetSprite;//�����Ŀ��Ӣ��
	target_hero = targetHero;//�����Ŀ��Ӣ��
	target = targetHero->sprite->getPosition();//Ŀ��λ��
	hurt = h;//�ӵ��˺�
	sprite = Sprite::create(name + ".png");
	sprite->setPosition(loc);//locΪ�����ӵ���Ӣ�۵�λ��
	isAOE = AOE;
}

bool Bullet::Hitted()
{
	//�ж��Ƿ����
	return sprite->getPositionX() == target.x && sprite->getPositionY() == target.y;
}

bool Bullet::HitHero()
{
	//Ŀ��λ����Ӣ��λ���Ƿ�һ��
	float distance_x = target_hero->sprite->getPositionX() - target.x;
	float distance_y = target_hero->sprite->getPositionY() - target.y;
	float distance = distance_x * distance_x + distance_y * distance_y;
	return distance <= plaid * plaid / 4;
}

void Bullet::Boom(vector<MyHero>& enemy)
{
	auto it = enemy.begin();
	while (it != enemy.end()) {
		float distance_x = it->sprite->getPositionX() - target.x;
		float distance_y = it->sprite->getPositionY() - target.y;
		float distance = distance_x * distance_x + distance_y * distance_y;
		if (distance <= plaid * plaid * 4) {
			it->current_hp -= hurt;
		}
		++it;
	}
}