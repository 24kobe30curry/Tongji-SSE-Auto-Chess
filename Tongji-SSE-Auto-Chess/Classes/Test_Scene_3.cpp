#include "Test.h"

void Test_Scene_3()
{
    auto myScene = Scene::create();//�����³���
    Director::getInstance()->pushScene(myScene);//����ǰ�����еĳ�����ͣ��ѹ�뵽����ջ�У���������ĳ�������Ϊ��ǰ���г���

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //����Ϊ��Ĳ��Դ��루����ΪmyScene��
    ///////////////////////////////
    auto mySprite = Sprite::create("mingrixiang.png");//��������
    mySprite->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2));
    mySprite->setScale(0.5f);
    myScene->addChild(mySprite, 1);//���볡��
    
    //��������
   /******************************************/
  
    mySprite->setPosition(50, 56);

    // create a few Actions
    auto moveBy = MoveBy::create(2.0f, Vec2(500, 0));
    auto scaleBy = ScaleBy::create(2.0f, 2.0f);
    auto delay = DelayTime::create(2.0f);

    // create a sequence
    auto delaySequence = Sequence::create(delay, delay->clone(), delay->clone(),
        delay->clone(), nullptr);

    auto sequence = Sequence::create(moveBy, delay, scaleBy, delaySequence, nullptr);

    // run it
    mySprite->runAction(sequence);

    // reverse it
    mySprite->runAction(sequence->reverse());
    /*****************************************/
    
    ///////////////////////////////


    //�˳���ǰ�����İ�ť
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//�ͷŵ�ǰ�������ٴӳ���ջ�е���ջ���ĳ���������������Ϊ��ǰ���г�����
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
    float y = origin.y + closeItem->getContentSize().height / 2;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    myScene->addChild(exitMenu, 1);
}