
#include "TestSocketIoScene.h"


Scene* TestSocketIo::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TestSocketIo::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestSocketIo::init()
{
    //
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }
    Size size = Director::getInstance()->getWinSize();
    client = nullptr;//��ʼ��Ϊ��ָ��

    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    addChild(menu);



    auto lblInit = Label::create("init socket", "Arial", 22);
    auto menuInit = MenuItemLabel::create(lblInit, [=](Ref* sender) {
        //1.connect��������ʵ��
        client = SocketIO::connect("ws://192.168.1.102:3000", *this);
        client->setTag("init socket");
        //4.��ʼ����ʱ������һ����������ʹ��on�����¼��ͻ�ȡ���յ�������
        client->on("loginresult", [=](SIOClient* client, const std::string& data) {//ʹ��C++��������ʵ��
            log("login result is :%s", data.c_str());
            });
        });
    menuInit->setPosition(size / 2);
    menu->addChild(menuInit);




    auto lblSend = Label::create("send message", "Arial", 22);
    auto menuSend = MenuItemLabel::create(lblSend, [=](Ref* sender) {
        //2.send������������
        client->send("hello socket.io");
        });
    menuSend->setPosition(size.width / 2, size.height / 2 - 50);
    menu->addChild(menuSend);



    auto lblSendEvent = Label::create("emit event", "Arial", 22);
    auto menuSendEvent = MenuItemLabel::create(lblSendEvent, [=](Ref* sender) {
        //3.�����������login�¼����������ֺ����봫��������  
        client->emit("login", "[{\"name\":\"myname\",\"pwd\":\"mypwd\"}]");
        });
    menuSendEvent->setPosition(size.width / 2, size.height / 2 - 100);
    menu->addChild(menuSendEvent);




    return true;
}

void TestSocketIo::onConnect(SIOClient* client) {
    log("onConnect");
    log("%s connect", client->getTag());
}

void TestSocketIo::onMessage(SIOClient* client, const std::string& data) {
    log("onMessage");
    log("%s received content is:%s", client->getTag(), data.c_str());
}

void TestSocketIo::onClose(SIOClient* client) {
    log("onClose");
    log("%s is closed", client->getTag());
}
void TestSocketIo::onError(SIOClient* client, const std::string& data) {
    log("onError");
    log("%s error is:%s", client->getTag(), data.c_str());
}

