#pragma once
#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

//��ͼ�����ڴ�ű���ͼƬ
class BackGroundLayer : public cocos2d::Layer
{
public:
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(BackGroundLayer);
};

#endif // __BACKGROUND_LAYER_H__  