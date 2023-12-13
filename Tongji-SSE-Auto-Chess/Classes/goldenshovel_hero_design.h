#pragma once
#include<iostream>
using namespace std;

/*====================����====================*/
//ע�⣺�û���Ϊ������࣬����ֱ�����ɶ���
class MyObject{
public:
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // ���캯��
		current_hp(hp), current_xp(xp), armor_value(av), location_x(x), location_y(y) {};

	virtual void my_move(int new_x, int new_y) = 0;                                        // �ƶ����������麯����


protected:
	int full_hp;                                  // ��Ѫ
	int current_hp;                               // ��ǰѪ��
	int current_xp;                               // ��ǰ����
	int armor_value;                              // ����ֵ

	int location_x;			                      // ������
	int location_y;                               // ������

	Sprite* sprite;
};

/*====================������====================*/
class MySprite:public MyObject  {
public:
	MySprite(int level, int hp, int xp, int av, int x = -1, int y = -1) :        // ���캯��
		MyObject(hp, xp, av, x, y), star_level(level) {};
	virtual void my_move(int new_x, int new_y);                                  // �ƶ�����

private:
	int star_level;     // �Ǽ�
};

/*====================Ӣ����====================*/
class MyHero : public MyObject {
public:
	MyHero(int index, int cost, int level, int power, int a_power, int n_c_r, int c_c_r, int hp, int xp, int av, int x = -1, int y = -1) : // ���캯��
		MyObject(hp, xp, av, x, y),
		battle_index(index), gold_cost(cost), star_level(level), attack_power(power), ace_attack_power(a_power),
		needed_cooldown_round(n_c_r), current_cooldown_round(c_c_r) {};
	virtual void my_move(int new_x, int new_y);  // �ƶ�����
    void seek_enemy();                           // ���к���
	void hero_ultimate();                        // ���к���

private:
	bool battle_index;                 // �ж��Ƿ��ڳ�
	int gold_cost;                     // Ӣ�ۻ��� 
    int star_level;                    // �Ǽ�
	int attack_power;                  // ������
	int ace_attack_power;              // ���й�����
	int needed_cooldown_round;         // ����������ȴ����
    int current_cooldown_round;        // ��ǰ��ȴ����
};