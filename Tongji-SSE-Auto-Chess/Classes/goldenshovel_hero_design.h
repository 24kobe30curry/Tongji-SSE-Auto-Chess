#pragma once
#include<iostream>
using namespace std;

#define max_hero_grade 3            //Ӣ������Ǽ� 

class goldenshovel_hero {
public:
	goldenshovel_hero();

	string hero_name;                //Ӣ����
	string ace_name;                 //��������
	int belongs_to;					 //��ǰ�������ڵ�ССӢ�۵ı��
	
	//int star_rating;                 //Ӣ���Ǽ�
	int gold_cost;                   //Ӣ�ۻ��� 

	int needed_charge_round;         //����������������
	int current_charge_round;        //��ǰ��������

	int attack_speed;                //�����ٶ� 
	int attack_distance;             //��������
	int attack_power;                //������
	int ace_attck_power;             //���й�����

	int full_hp;                     //��ѪѪ��
	int current_hp;                  //��ǰѪ��
	//int magic_resistance;            //ħ�� 
	//int physical_resistance;         //�￹ 
	//int armor_value;                 //����ֵ 

	//int search_enemy_num=1;          //�������� 
	
	//��¼��ǰӢ���������ϵ�λ��
	int location_x = -1;			 //������
	int location_y = -1;             //������
private:
};
