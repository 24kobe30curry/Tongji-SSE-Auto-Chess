#include "Test.h"

void Test_Scene_3()
{
    auto myScene = Scene::create();//�����³���
    Director::getInstance()->pushScene(myScene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����Ϊ��Ĳ��Դ��루����ΪmyScene��
    ///////////////////////////////
    

    auto label1 = Label::createWithTTF("My Game", "fonts/Marker Felt.ttf", 36);
    label1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

    myScene->addChild(label1);

    auto sprite1 = Sprite::create("mingrixiang.png");
    sprite1->setPosition(Vec2(100, 100));

    myScene->addChild(sprite1);
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

/***********************************************************************************************************************************************/
#include <iostream>
using namespace std;

class Object {
public:
    Object();
    virtual void move(int new_x, int new_y);
protected:
    int health;
    int experience;
    int armor;
    int x;
    int y;
};

class HeroBranch : public Object {
public:
    HeroBranch();
    void attack();
    void displayInfo();

private:
    int attack_damage;
    int star_level;
};

class SpriteBranch : public Object {
public:
    SpriteBranch();
    void displayInfo();
private:
    int star_level;
};