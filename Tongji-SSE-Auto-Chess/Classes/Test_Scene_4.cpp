#include "Test_Scene_4.h"

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

    return true;
}

void Test_Scene_4::loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    // �����ﴦ���¼�߼�����������ͨ����֤�˺�����

    // ʾ�����򵥴�ӡ������˺ź�����
    CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());
}


void Test_Scene_4::registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    // �����ﴦ��ע���߼�����������ͨ�ű������˺�����

    // ʾ�����򵥴�ӡ������˺ź�����
    CCLOG("Register: Account: %s, Password: %s", account.c_str(), password.c_str());
}