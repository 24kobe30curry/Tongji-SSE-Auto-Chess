#pragma once
#include<iostream>
using namespace std;

#define max_hero_grade 3            //Ӣ����ߵȼ� 

class goldenshovel_hero {
public:
	goldenshovel_hero();

	string hero_name;                //Ӣ����
	string ace_name;                 //��������
	
	int star_rating;                 //Ӣ���Ǽ�
	int max_grade=max_hero_grade;    //Ӣ����ߵȼ� 
	int current_grade;               //Ӣ�۵ȼ� 
	int gold_cost;                   //Ӣ�ۻ��� 

	int needed_charge_round;         //����������������
	int current_charge_round;        //��ǰ��������

	int attack_speed;                //�����ٶ� 
	int attack_distance;             //��������
	int attack_power;                //������
	int ace_attck_power;             //���й�����

	int full_hp;                     //��ѪѪ��
	int current_hp;                  //��ǰѪ��
	int magic_resistance;            //ħ�� 
	int physical_resistance;         //�￹ 
	int armor_value;                 //����ֵ 

	int search_enemy_num=1;          //�������� 
	
	
private:
};
