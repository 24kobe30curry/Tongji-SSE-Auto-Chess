#include "goldenshovel_hero_design.h"
#include <map>
#include <string>

std::map<std::string, MyHero> Hero_list = {
	//�ο���վ https://tftactics.gg/champions  https://lol.qq.com/tft/#/champion


	//һ��
	//���� https://lol.qq.com/tft/#/championDetail/1
	{"Annie", MyHero(0, 1, 1, 40, 70, 7, 0, 4, 0.7, 500, -1, -1)},
	//���� https://lol.qq.com/tft/#/championDetail/42
	{"Corki", MyHero(0, 1, 1, 48, 80, 8, 0, 4, 0.7, 450, -1, -1)},
	//����� https://lol.qq.com/tft/#/championDetail/44
	{"Taric", MyHero(0, 1, 1, 55, 60, 12, 0, 1, 0.55, 650, -1, -1)},
	//��ܽ�� https://lol.qq.com/tft/#/championDetail/12
	{"Evelynn", MyHero(0, 1, 1, 45, 60, 12, 0, 1, 0.7, 550, -1, -1)},


	//����
	//����
	{"Kayle", MyHero(0, 2, 1, 35, 100, 12, 0, 3, 0.75, 550, -1, -1)},
	//����
	{"Garen", MyHero(0, 2, 1, 55, 90, 12, 0, 1, 0.7, 750, -1, -1)},
	//����
	{"Twitch", MyHero(0, 2, 1, 50, 100, 12, 0, 5, 0.7, 550, -1, -1)},
	//����
	{"Senna", MyHero(0, 2, 1, 40, 80, 12, 0, 6, 0.7, 600, -1, -1)},


	//����
	//��ľľ https://tftactics.gg/champions/amumu
	{"Amumu", MyHero(0, 3, 1, 45, 100, 12, 0, 1, 0.65, 550, -1, -1)},
	//¬��˹ https://tftactics.gg/champions/lux
	{"Lux", MyHero(0, 3, 1, 40, 100, 12, 0, 4, 0.7, 700, -1, -1)},
	//���׶� https://tftactics.gg/champions/samira
	{"Samira", MyHero(0, 3, 1, 60, 100, 12, 0, 4, 0.7, 600, -1, -1)},
	//��� https://tftactics.gg/champions/neeko
	{"Neeko", MyHero(0, 3, 1, 50, 100, 12, 0, 4, 0.6, 850, -1, -1)}
	// ... ����Ӣ��
};
const MyHero one_fee[4] = { Hero_list.at("Annie"), Hero_list.at("Corki"), Hero_list.at("Taric"), Hero_list.at("Evelynn") };
const MyHero two_fee[4] = { Hero_list.at("Kayle"), Hero_list.at("Garen"), Hero_list.at("Twitch"), Hero_list.at("Senna") };
const MyHero three_fee[4] = { Hero_list.at("Amumu"), Hero_list.at("Lux"), Hero_list.at("Samira"), Hero_list.at("Neeko") };
