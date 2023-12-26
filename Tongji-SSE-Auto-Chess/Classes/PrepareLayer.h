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

    int player;//玩家1

    void addHero(vector<MyHero>& Hero, int, int);//英雄加入场上

    void store_display();//商店显示
    void card_remove(int index);//选中的卡片移除

    void error_display(const std::string& displayText);
    void error_window_close();

    /*==============监听器回调函数=================*/
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

private:
    int select_index; // 用于存储当前选中的备战席上的英雄的索引
    Vec2 initial_position;// 用于存储英雄的起始坐标
};

#endif // __PREPARE_LAYER_H__  
