//#include <goldenshovel_hero_design.h>
#include "HelloWorldScene.h"
#include "Test_Scene_2.h"

USING_NS_CC;




Scene* Test_Scene_2::createScene()
{
    return Test_Scene_2::create();
}

bool Test_Scene_2::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    //...
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
    this->addChild(exitMenu, 1);

    return true;
}

void Test_Scene_2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

#define attack_ace 1    //�����Դ���
#define treat_ace 2     //�����ʹ���

//void MyHero::hero_ultimate(int ace_mode)                        // ���к���
//{
//    MyHero* attacking_hero;  //�����,�պ�����
//    
//    bool is_attacking = (attacking_hero != NULL);
//    if (!is_attacking) {
//        //seek_enemy();  //�������к���
//    }
//    //this->Sprite->perform_ace();//�ͷŴ��еĶ����������
//    if(ace_mode==attack_ace)
//    {
//        if (!(ace_attack_power < attacking_hero->current_hp)) {  //ֱ�ӻ�ɱ
//            attacking_hero->current_hp = 0;
//            attacking_hero->sprite->minus_hp_animation();//��Ѫ������
//            //attacking_hero->to_death();//����Ч��(�����)
//            battle_secne->removeChild(attacking_hero); //�ڶ�ս�������Ƴ����������������Ⱦ
//        }
//        else {      //δֱ�ӻ�ɱ
//            attacking_hero->current_hp -= ace_attack_power;
//            attacking_hero->sprite->minus_hp_animation();//��Ѫ������
//        }
//    }
//    else if (ace_mode == treat_ace) {        
//        if (ace_attack_power < (attacking_hero->full_hp - current_hp)) {     //����Ѫ
//            attacking_hero->current_hp +=ace_attack_power;
//            attacking_hero->sprite->add_hp_animation();//��Ѫ������
//        }
//        else {      //��������Ѫ
//            attacking_hero->current_hp = full_hp;
//            attacking_hero->sprite->add_hp_animation();//��Ѫ������
//        }
//    }
//}