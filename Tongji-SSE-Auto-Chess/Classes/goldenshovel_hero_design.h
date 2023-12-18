#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200

#define attack_ace 1    //�����Դ���
#define treat_ace 2     //�����ʹ���
/*====================����====================*/
//ע�⣺�û���Ϊ������࣬����ֱ�����ɶ���
class MyObject {
public:
	MyObject() {};
	MyObject(int hp, int xp, int av, int x = -1, int y = -1) :                             // ���캯��
		current_hp(hp), /*current_xp(xp), armor_value(av),*/ location_x(x), location_y(y) {};

	//virtual void my_move(int new_x, int new_y) = 0;                                        // �ƶ����������麯����

	cocos2d::Sprite* sprite;                                                               // ָ��

protected:
	int full_hp;                                  // ��Ѫ
	int current_hp;                               // ��ǰѪ��

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
	MyHero(int on_court, int gold_cost, int star_level, int attack_power, int ace_attack_power,
        int needed_cooldown_round, int current_cooldown_round, int attack_distance,double attack_cd, 
        int hp, /*int xp, int av,*/ int x = -1, int y = -1) : // ���캯��
		MyObject(hp,/* xp, av,*/ x, y),
        on_court(on_court), gold_cost(gold_cost), star_level(star_level), attack_power(attack_power), ace_attack_power(ace_attack_power),
		needed_cooldown_round(needed_cooldown_round), current_cooldown_round(current_cooldown_round), attack_distance(attack_distance),
        attack_cd(attack_cd){};
	//virtual void my_move(int new_x, int new_y);  // �ƶ�����
    inline void seek_enemy(MyHero hero);                           // ���к���
    inline void hero_attack();                           //��������
    inline void hero_ultimate(int ace_mode);                       // ���к���

	MyHero* current_enemy;
private:
	bool on_court;                 // �ж��Ƿ��ڳ�
	int gold_cost;                     // Ӣ�ۻ��� 
	int star_level;                    // �Ǽ�
	int attack_power;                  // ������
	int ace_attack_power;              // ���й�����
	int needed_cooldown_round;         // ����������ȴ����
    int current_cooldown_round;        // ��ǰ��ȴ����
    double attack_cd;                     //����cd
    int attack_distance;
    // ��������
};

//Ӣ������
inline void MyHero::seek_enemy(MyHero hero) {
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

inline void MyHero::hero_attack() {
    if (current_enemy == NULL) {   //û�й���Ŀ����߹���Ŀ��������δ����Ѱ��Ŀ��
        seek_enemy(*this);
    }
    int last_attack_time;
    while (current_enemy != NULL) {
        last_attack_time = time(NULL);              //��¼������ʱ���
        //��������
        if (this->attack_power < current_enemy->current_hp) {  //����ֱ�ӻ�ɱ
            current_enemy->current_hp -= this->attack_power;
            //current_enemy->sprite->minus_hp(); //��Ѫ����
        }
        else {                                                 //ֱ�ӻ�ɱ
            current_enemy->current_hp = 0;
            //current_enemy->sprite->minus_hp(); //��Ѫ����
            current_enemy = NULL;
        }
        if (current_enemy == NULL)            //��ɱ�󽫵�����ΪNULL�˳�ѭ��
            break;
        while (1) {                             //����cd
            int now_time = time(NULL);
            if (now_time - last_attack_time >= attack_cd)
                break;
        }
    }
}

inline void MyHero::hero_ultimate(int ace_mode)                        // ���к���
{
    if (current_enemy == NULL) {
        seek_enemy(*this);  //�������к���
    }
    //this->Sprite->perform_ace();//�ͷŴ��еĶ����������
    if (ace_mode == attack_ace)
    {
        if (!(ace_attack_power < current_enemy->current_hp)) {  //ֱ�ӻ�ɱ
            current_enemy->current_hp = 0;
            //attacking_hero->sprite->minus_hp_animation();//��Ѫ������
        }
        else {      //δֱ�ӻ�ɱ
            current_enemy->current_hp -= ace_attack_power;
            //attacking_hero->sprite->minus_hp_animation();//��Ѫ������
        }
    }
    else if (ace_mode == treat_ace) {
        if (ace_attack_power < (current_enemy->full_hp - current_hp)) {     //����Ѫ
            current_enemy->current_hp += ace_attack_power;
            //attacking_hero->sprite->add_hp_animation();//��Ѫ������
        }
        else {      //��������Ѫ
            current_enemy->current_hp = full_hp;
            //attacking_hero->sprite->add_hp_animation();//��Ѫ������
        }
    }
}

extern std::map<std::string, MyHero> Hero_list;