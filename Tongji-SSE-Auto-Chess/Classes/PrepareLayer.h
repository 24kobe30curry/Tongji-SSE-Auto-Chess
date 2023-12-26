#pragma once
#ifndef __PREPARE_LAYER_H__
#define __PREPARE_LAYER_H__

#include "cocos2d.h"
#include "goldenshovel_hero_design.h"

class PrepareLayer : public cocos2d::Layer
{
public:
    virtual bool init(int index);
    static PrepareLayer* create(int index);
    void update(float dt);
    int player;//���1

<<<<<<< .merge_file_gfT9fK
    void addHero(int, int, int);//Ӣ�ۼ��볡��

=======
    void addHero(vector<MyHero>& Hero, int, int);//Ӣ�ۼ��볡��
    cocos2d::Label* expLabel;
    cocos2d::Label* moneyLabel;
    cocos2d::Label* levelLabel;
>>>>>>> .merge_file_tYK2ji
    void store_display();//�̵���ʾ
    void card_remove(int index);//ѡ�еĿ�Ƭ�Ƴ�

    void error_display(const std::string& displayText);
    void error_window_close();

    /*==============�������ص�����=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    int select_index; // ���ڴ洢��ǰѡ�еı�սϯ�ϵ�Ӣ�۵�����
    Vec2 initial_position;// ���ڴ洢Ӣ�۵���ʼ����
};

#endif // __PREPARE_LAYER_H__  
