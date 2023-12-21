//goldenshovel_hero_design.h
#pragma once
#include<iostream>
#include"HelloWorldScene.h"
using namespace std;
#define plaid_width 256
#define plaid_height 200

#define attack_ace 1    //�����Դ���
#define treat_ace 2     //�����ʹ���

#define map_width 9
#define map_height 6


class MyHero;

extern MyHero* GameMap[map_width][map_height];

/*====================����====================*/
//ע�⣺�û���Ϊ������࣬����ֱ�����ɶ���
class MyObject{
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
    inline void hero_attack(vector <MyHero>& Hero_fighting);                           //��������
    inline void hero_ultimate(int ace_mode);                       // ���к���
    int gethp() { return this->current_hp; };
    void decreasehp() { this->current_hp -= 100; };
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
    inline BOOL IsInMap(int x, int y);
    inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance);
    // ��������
};
inline BOOL IsInMap(int x, int y) {
    if (x < map_width && x >= 0 && y < map_height && y >= 0) {
        return 1;
    }
    return 0;
}
inline void Find_Way_To_attack(int X, int Y, int& HX, int& HY, int distance) {
    int deltaX = X - HX;
    int deltaY = Y - HY;

    // ����Խ��߾���
    int distanceToTarget = std::max(std::abs(deltaX), std::abs(deltaY));

    if (distanceToTarget <= distance) {
        // �����ǰ�����Ѿ�С�ڵ��ڹ������룬�����ƶ�
        return;
    }

    // �����ֵ����
    float t = static_cast<float>(distance) / distanceToTarget;

    // ʹ�ò�ֵ�����µ�λ��
    HX = static_cast<int>(HX + t * deltaX);
    HY = static_cast<int>(HY + t * deltaY);
}


//Ӣ������ MAP��֪�������ﶨ�壬Ъ������
inline void MyHero::seek_enemy(MyHero hero) {
    BOOL find = 0;
    int distance = 1;
    int i;
    int j;
    while (!find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (GameMap[hero.location_x + distance * i][hero.location_y + j * distance] != nullptr)//���Ӧ�����ж������������Ӣ�ۣ�ûд����
                {
                    hero.current_enemy = GameMap[hero.location_x + distance * i][hero.location_y + j * distance];
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    while (hero.current_enemy->current_hp != 0) {
        if (hero.current_enemy->location_x - hero.location_x > hero.attack_distance) {
            GameMap[location_x][location_y] = nullptr;
            Find_Way_To_attack(hero.current_enemy->location_x, hero.current_enemy->location_y, hero.location_x, hero.location_y, hero.attack_distance);
            GameMap[location_x][location_y] = &hero;
            //hero.sprite ���moveby��moveto����ûд
        }
    }
}





inline void MyHero::hero_attack(vector <MyHero>& Hero_fighting) {
    //��ĿǰӢ��û�������ҵ���û��������ǰcurrent_enemy���˵�ʱ������һ������
    if (current_enemy == NULL || this->current_hp != 0 || Hero_fighting.empty() != 1) {
        seek_enemy(*this);
        return;
    }
    int last_attack_time;
    while (current_enemy != NULL && this->current_hp!= 0) {
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
extern string one_fee[4];
extern string two_fee[4];
extern string three_fee[4];
extern string four_fee[4];
extern string five_fee[4];

extern vector <MyHero> Hero_on_court_1;
extern vector <MyHero> Hero_on_court_2;
extern vector <MyHero> Hero_select_1;
extern vector <MyHero> Hero_select_2;
extern vector <MyHero> Hero_fighting_1;
extern vector <MyHero> Hero_fighting_2;

//�����С�������ˢ�µ��̵����
extern string Hero_1[5];
extern string Hero_2[5];


void make_a_random_hero(int fee[], string Hero_in_shop[]);
MyHero set_a_hero(string hero_name, string Hero_in_shop[], vector<MyHero>& Hero);