//goldenshovel_hero_design.h
#pragma once
#include<iostream>
#include"HelloWorldScene.h"
#include<vector>
#include "thread_pool.h"
#include "cocos2d.h"
#include"Test_Scene_2.h"

using namespace std;
#define plaid_width 256
#define plaid_height 200

#define attack_ace 1    //�����Դ���
#define treat_ace 2     //�����ʹ���

#define map_width 9
#define map_height 6

#define MAX_LEVEL 7

class MyHero;

extern MyHero* GameMap[map_width][map_height];

/*====================����====================*/
//ע�⣺�û���Ϊ������࣬����ֱ�����ɶ���
class MyObject{
public:
	MyObject() {};
	MyObject(int hp,/* int xp, int av,*/ int x = -1, int y = -1) :                             // ���캯��
		current_hp(hp), /*current_xp(xp), armor_value(av),*/ location_x(x), location_y(y) {};

	//virtual void my_move(int new_x, int new_y) = 0;                                        // �ƶ����������麯����

	cocos2d::Sprite* sprite;
    int gethp() { return this->current_hp; };                                                // ָ��

protected:
	int full_hp;                                  // ��Ѫ
	int current_hp;                               // ��ǰѪ��

    int location_x;			                      // ������
    int location_y;                               // ������
};


/*====================Ӣ����====================*/
class MyHero : public MyObject {
    friend class BattleLayer;
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
    inline void seek_enemy();                           // ���к���
    inline void hero_attack(thread_pool &tp);                           //��������
    inline void hero_ultimate(int ace_mode);                       // ���к���
    int getcost() { return this->gold_cost; };
    void decreasehp() { this->current_hp -= 100; };
	MyHero* current_enemy;
    int getcurrent_hp() { return current_hp; }
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

inline void MyHero::seek_enemy() {
    BOOL find = 0;
    int distance = 1;
    int i;
    int j;
    while (!find) {
        for (i = -1; i < 1; i++) {
            for (j = -1; j < 1; j++) {
                if (i == 0 && j == 0) continue;
                if (GameMap[this->location_x + distance * i][this->location_y + j * distance] != nullptr)//���Ӧ�����ж������������Ӣ�ۣ�ûд����
                {
                    this->current_enemy = GameMap[this->location_x + distance * i][this->location_y + j * distance];
                    find = 1;
                    break;
                }
                if (find == 1)
                    break;
            }
        }
        distance++;
    }
    while (this->current_enemy->current_hp != 0) {
        if (this->current_enemy->location_x - this->location_x > this->attack_distance) {
            GameMap[location_x][location_y] = nullptr;
            Find_Way_To_attack(this->current_enemy->location_x, this->current_enemy->location_y, this->location_x, this->location_y, this->attack_distance);
            GameMap[location_x][location_y] = this;
            //this->.sprite ���moveby��moveto����ûд
        }
    }
}

inline void MyHero::hero_attack(thread_pool& tp){
    //��ĿǰӢ��û�������ҵ���û��������ǰcurrent_enemy���˵�ʱ������һ������
    if (current_enemy == NULL) {    
        //seek_enemy();
        return;
    }

    auto lambda = [this] {
        int last_attack_time;
        while (this!=NULL&&this->current_enemy != NULL && this->current_enemy->current_hp != 0 && this->current_hp != 0) {
            last_attack_time = time(NULL);              //��¼������ʱ���
            //���й���
            if (current_cooldown_round == needed_cooldown_round) {
                last_attack_time = time(NULL);
                this->hero_ultimate(1);
                this->current_cooldown_round = 0;
            }
            //��ͨ����
            else{
                if (this->attack_power < this->current_enemy->current_hp) {  //����ֱ�ӻ�ɱ
                    this->current_enemy->current_hp -= this->attack_power;
                    //my->current_enemy->sprite->minus_hp(); //��Ѫ����
                    this->current_cooldown_round += 1;
                }
                else {                                                 //ֱ�ӻ�ɱ
                    this->current_enemy->current_hp = 0;
                    //current_enemy->sprite->minus_hp(); //��Ѫ����
                    this->current_enemy = NULL;
                    this->current_cooldown_round += 1;
                }
            }
            if (this->current_enemy == NULL)            //��ɱ�󽫵�����ΪNULL�˳�ѭ��
                break;
            while (1) {                             //����cd
                int now_time = time(NULL);
                if (now_time - last_attack_time >= attack_cd)
                    break;
            }
        }
    };
    tp.enqueue(lambda);
}

inline void MyHero::hero_ultimate(int ace_mode)                        // ���к���
{
    if (current_enemy == NULL) {
        return;
        //seek_enemy();  //�������к���
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



class MySprite;
extern vector<MySprite> Player;
extern std::map<std::string, MyHero> Hero_list;
extern int Posibility_Of_Hero[MAX_LEVEL][5];
extern string one_fee[4];
extern string two_fee[4];
extern string three_fee[4];
extern string four_fee[4];
extern string five_fee[4];
extern int level_up_exp[6];


/*====================������====================*/
class MySprite :public MyObject {
    friend class BattleLayer;
public:
    MySprite() {};
    MySprite(int level, int hp,/* int xp, int av,*/ int money, int x = -1, int y = -1) :        // ���캯��
        MyObject(hp/*, xp, av*/, x, y), star_level(level) {};
    //virtual void my_move(int new_x, int new_y);                                  // �ƶ�����

    bool operator==(const MySprite& other) const {
        // �������ж����� MySprite �����Ƿ����
        return this->location_x == other.location_x && this->location_y == other.location_y;
    }
    inline void refresh_shop();//ˢ���̵�Ӣ��
    inline void make_a_random_hero();   //�����̵�Ӣ��
    inline void erase_a_player();//ɾ�����˸����
    inline void MySprite::set_a_hero(string hero_name);//��һ��Ӣ�۴��̵�ѡ��
    inline void level_up(){ if (this->current_exp >= level_up_exp[this->star_level]) { this->current_exp = 0; this->star_level++; } }//ССӢ�������ж�
private:
    int star_level;     // �Ǽ�
    int max_hero = star_level + 2;//���Ӣ������
    int money;          //��ǰ��Ǯ��
    vector<MyHero> Hero_on_court;//��ǰ��ӵ�е�Ӣ�ۣ��ڳ��ϵģ�
    vector<MyHero> Hero_on_bench;//��ǰ��սϯ�ϵ�Ӣ��
    vector<MyHero> Hero_fighting;//ս��ʱ���ڴ��Ӣ�۵���ʱ�ռ�
    string Hero_in_shop[5];      //�̵��е�Ӣ��
    MySprite* current_enemy;
    int current_exp;    //��ǰ�еľ���ֵ
};

inline void MySprite::erase_a_player() {
    auto it = std::find(Player.begin(), Player.end(), *this);

    // ����Ƿ��ҵ���ǰ����
    if (it != Player.end() && it->gethp() == 0) {
        // ʹ�õ�����ɾ��Ԫ��
        Player.erase(it);
    }
}

inline void MySprite::make_a_random_hero() {
    int i;
    string hero_compose[100];
    for (i = 0; i < Posibility_Of_Hero[this->star_level][1]; i++) {
        hero_compose[i] = one_fee[std::rand() % sizeof(one_fee) + 1];
    }
    for (; i < Posibility_Of_Hero[this->star_level][1] + Posibility_Of_Hero[this->star_level][2]; i++) {
        //ͬ
        hero_compose[i] = two_fee[this->star_level][std::rand() % sizeof(two_fee[this->star_level]) + 1];
    }
    for (; i < Posibility_Of_Hero[this->star_level][1] + Posibility_Of_Hero[this->star_level][2] + Posibility_Of_Hero[this->star_level][3]; i++) {
        //ͬ
        hero_compose[i] = three_fee[this->star_level][std::rand() % sizeof(three_fee[this->star_level]) + 1];
    }
    for (; i < Posibility_Of_Hero[this->star_level][1] + Posibility_Of_Hero[this->star_level][2] + Posibility_Of_Hero[this->star_level][3] + Posibility_Of_Hero[this->star_level][4]; i++) {
        //ͬ
        hero_compose[i] = four_fee[this->star_level][std::rand() % sizeof(four_fee[this->star_level]) + 1];
    }
    for (; i < Posibility_Of_Hero[this->star_level][1] + Posibility_Of_Hero[this->star_level][2] + Posibility_Of_Hero[this->star_level][3] + Posibility_Of_Hero[this->star_level][4] + Posibility_Of_Hero[this->star_level][5]; i++) {
        //ͬ
        hero_compose[i] = five_fee[this->star_level][std::rand() % sizeof(five_fee[this->star_level]) + 1];
    }
    for (int i = 0; i < 5; i++) {
        if (this->Hero_in_shop[i] == "") {
            this->Hero_in_shop[i] = hero_compose[std::rand() % 100 + 1];
        }
    }
}

inline void MySprite::refresh_shop() {
    if (this->money < 2) {
        //������ʾ��д
    }
    else {
        this->money -= 2;//ˢ�¿۳����
        for (int i = 0; i < 5; i++) {
            this->Hero_in_shop[i] = "";
        }
        make_a_random_hero();
    }
}

//��һ����Ӣ�۴��̵���ѡ��,pjl�Ѿ�д�����ӻ�ʵ�֣���Ҫ������ϲ�һ��
inline void MySprite::set_a_hero(string hero_name) {
    for (int i = 0; i < 5; i++) {
        if (this->Hero_in_shop[i] == hero_name) {
            this->Hero_in_shop[i] = "";
        }
    }

    //��Ǯ
    if (this->money < Hero_list[hero_name].getcost()) {
        //������ʾ��д
    }
    else {
        this->money -= Hero_list[hero_name].getcost();
        string filename = hero_name + ".png";
        MyHero set_a_new_hero = Hero_list.at(hero_name);
        //pjl���һ������Ĵ���
        /*auto new_hero_Sprite = Sprite::create(filename);
        set_a_new_hero.sprite = new_hero_Sprite;
        this->Hero_on_bench.push_back(set_a_new_hero);*/


        //�������Ҫ�������Ǻ�һ�������ټ�
        //���ӻ�������position��ֵ
    }
}


//��ɾ��
extern vector <MyHero> Hero_on_court_1;
extern vector <MyHero> Hero_on_court_2;
extern vector <MyHero> Hero_select_1;
extern vector <MyHero> Hero_select_2;
extern vector <MyHero> Hero_fighting_1;
extern vector <MyHero> Hero_fighting_2;

//�����С�������ˢ�µ��̵����
extern string Hero_1[5];
extern string Hero_2[5];

//��ɾ��
MyHero set_a_hero(string hero_name, string Hero_in_shop[], vector<MyHero>& Hero);

