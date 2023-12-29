#include "Test_Scene_4.h"
#include"Client.h"

USING_NS_CC;

Scene* Test_Scene_4::createScene()
{
    return Test_Scene_4::create();
}

bool Test_Scene_4::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto layout = cocos2d::ui::Layout::create();
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(cocos2d::Color3B(100, 149, 237));

    auto accountInput = cocos2d::ui::TextField::create("�������˺�", "Arial", 30);
    accountInput->setPosition(Vec2(240, 400));
    accountInput->setPlaceHolderColor(cocos2d::Color4B::GRAY);
    accountInput->setPlaceHolder("Enter your account");
    accountInput->setCursorEnabled(true);  // ���ù��
    layout->addChild(accountInput);

    auto passwordInput = cocos2d::ui::TextField::create("����������", "Arial", 30);
    passwordInput->setPosition(Vec2(240, 320));
    passwordInput->setPasswordEnabled(true);
    passwordInput->setPasswordStyleText("*");
    passwordInput->setCursorEnabled(true);  // ���ù��
    layout->addChild(passwordInput);

    auto registerButton = cocos2d::ui::Button::create("join.png");
    registerButton->setPosition(Vec2(240, 100));
    registerButton->addClickEventListener(CC_CALLBACK_1(Test_Scene_4::registerButtonCallback, this, accountInput, passwordInput));
    layout->addChild(registerButton);

    auto loginButton = cocos2d::ui::Button::create("login.png");
    loginButton->setPosition(Vec2(240, 160));
    loginButton->addClickEventListener(CC_CALLBACK_1(Test_Scene_4::loginButtonCallback, this, accountInput, passwordInput));
    layout->addChild(loginButton);

    addChild(layout);

    //�˳���ǰ�����İ�ť
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
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

void Test_Scene_4::loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    char str_ac[max_ac_num] = { 0 };
    str_ac[max_ac_num] = '\0';
    copy(account.begin(), account.end(), str_ac);
    char str_pw[max_ac_pw] = { 0 };
    str_ac[max_ac_pw] = '\0';
    copy(account.begin(), account.end(), str_pw);
    // �����ﴦ���¼�߼�����������ͨ����֤�˺�����
    Client::getInstance()->write_event(Login);
    Client::getInstance()->write_account(str_ac);
    Client::getInstance()->write_password(str_pw);
    Client::getInstance()->send_msg();
    Sleep(0.5);
    if(Client::getInstance() ->csocket._passInfo->_result==1)
        CCLOG("success login");
    else
        CCLOG("fail to login");
    // ʾ�����򵥴�ӡ������˺ź�����
   // CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());
}


void Test_Scene_4::registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    // �����ﴦ��ע���߼�����������ͨ�ű������˺�����

    // ʾ�����򵥴�ӡ������˺ź�����
    CCLOG("Register: Account: %s, Password: %s", account.c_str(), password.c_str());
}