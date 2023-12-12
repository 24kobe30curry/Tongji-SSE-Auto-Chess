#include "Test.h"

void Test_Scene_1()
{
    auto myScene = Scene::create();//�����³���
    Director::getInstance()->pushScene(myScene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����Ϊ��Ĳ��Դ��루����ΪmyScene��
    ///////////////////////////////

    auto mySprite = Sprite::create("kunkun.png");//��������
    mySprite->setPosition(Vec2(origin.x+ visibleSize.width/2,
        origin.y+ visibleSize.height/2));
    mySprite->setScale(0.5f);
    myScene->addChild(mySprite, 1);//���볡��
    

    ///////////////////////////////

    //�˳���ǰ�����İ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//�ͷŵ�ǰ�������ٴӳ���ջ�е���ջ���ĳ���������������Ϊ��ǰ���г�����
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    myScene->addChild(exitMenu, 1);
}