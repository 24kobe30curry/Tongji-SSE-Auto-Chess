#pragma once
#ifndef __STORE_LAYER_H__
#define __STORE_LAYER_H__

#include "cocos2d.h"
#include "HeroLayer.h"

//��ͼ���������̵�
class StoreLayer : public cocos2d::Layer
{   
public:
    virtual bool init();

    HeroLayer* herolayer;   //Ŀ��㣬�����̵���뵽���Ǹ�ͼ��
    void addShop();

    // implement the "static create()" method manually
    CREATE_FUNC(StoreLayer);
};

#endif // __STORE_LAYER_H__  