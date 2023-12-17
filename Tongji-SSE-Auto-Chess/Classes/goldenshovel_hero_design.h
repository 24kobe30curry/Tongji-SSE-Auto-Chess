#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200
/*====================����====================*/
//ע�⣺�û���Ϊ������࣬����ֱ�����ɶ���
class MyObject {
public:
	MyObject() {};
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // ���캯��
		current_hp(hp), current_xp(xp), armor_value(av), location_x(x), location_y(y) {};

	//virtual void my_move(int new_x, int new_y) = 0;                                        // �ƶ����������麯����

	cocos2d::Sprite* sprite;                                                               // ָ��

protected:
	int full_hp;                                  // ��Ѫ
	int current_hp;                               // ��ǰѪ��
	int current_xp;                               // ��ǰ����
	int armor_value;                              // ����ֵ

    int location_x;			                      // ������
    int location_y;                               // ������
};

/*====================������====================*/
class MySprite:public MyObject  {
public:
	MySprite() {};
	MySprite(int level, int hp, int xp, int av, int x = -1, int y = -1) :        // ���캯��
		MyObject(hp, xp, av, x, y), star_level(level) {};
	//virtual void my_move(int new_x, int new_y);                                  // �ƶ�����

private:
	int star_level;     // �Ǽ�
};

/*====================Ӣ����====================*/
class MyHero : public MyObject {
public:
	MyHero() {};
	MyHero(int index, int cost, int level, int power, int a_power, int n_c_r, int c_c_r, int ad, int hp, int xp, int av, int x = -1, int y = -1) : // ���캯��
		MyObject(hp, xp, av, x, y),
		battle_index(index), gold_cost(cost), star_level(level), attack_power(power), ace_attack_power(a_power),
		needed_cooldown_round(n_c_r), current_cooldown_round(c_c_r), attack_distance(ad) {};
	//virtual void my_move(int new_x, int new_y);  // �ƶ�����
	void seek_enemy(MyHero hero, vector<MyHero>& Hero_on_court);                           // ���к���
	void hero_ultimate();                        // ���к���

	MyHero* current_enemy;
private:
	bool battle_index;                 // �ж��Ƿ��ڳ�
	int gold_cost;                     // Ӣ�ۻ��� 
	int star_level;                    // �Ǽ�
	int attack_power;                  // ������
	int ace_attack_power;              // ���й�����
	int needed_cooldown_round;         // ����������ȴ����
	int current_cooldown_round;        // ��ǰ��ȴ����
	int attack_distance;               // ��������
};

//Ӣ������
void MyHero::seek_enemy(MyHero hero, vector <MyHero>& Hero_on_court) {
    BOOL find = 0;
    int distance = 1;
    int i;
    int j;
    MyHero enemy;
    while (!find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (hero.location_x + distance * i * plaid_width, hero.location_y + j * distance * plaid_height)//���Ӧ�����ж������������Ӣ�ۣ�ûд����
                {
                    hero.current_enemy = &enemy;//�˴��ڶ���heroӦ�øĳ������ҵ������Ӣ��
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    while (enemy.current_hp) {
        if (enemy.location_x - hero.location_x > hero.attack_distance * plaid_width) {
            hero.location_x = enemy.location_x + hero.attack_distance * plaid_width * (hero.location_x - enemy.location_x) / abs(hero.location_x - enemy.location_x);
            hero.location_y = enemy.location_y + hero.attack_distance * plaid_height * (hero.location_y - enemy.location_y) / abs(hero.location_y - enemy.location_y);
            //hero.sprite ���moveby��moveto����ûд
        }
    }
}