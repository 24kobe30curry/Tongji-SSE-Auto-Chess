//#include <goldenshovel_hero_design.h>
#include "HelloWorldScene.h"
#include "Test_Scene_2.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

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
    // �����������������������ؼ�
    auto bgmSlider = ui::Slider::create();
    bgmSlider->loadBarTexture("slider_progress.png");
    bgmSlider->loadSlidBallTextures("slider_ball.png", "slider_ball.png", "");
    bgmSlider->loadProgressBarTexture("slider_progress.png");
    bgmSlider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6));
    bgmSlider->addEventListener(CC_CALLBACK_2(Test_Scene_2::bgmSliderCallback, this));
    this->addChild(bgmSlider);

    // ������Ч�����������ؼ�
    auto sfxSlider = ui::Slider::create();
    sfxSlider->loadBarTexture("slider_progress.png");
    sfxSlider->loadSlidBallTextures("slider_ball.png", "slider_ball.png", "");
    sfxSlider->loadProgressBarTexture("slider_progress.png");
    sfxSlider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    sfxSlider->addEventListener(CC_CALLBACK_2(Test_Scene_2::sfxSliderCallback, this));
    this->addChild(sfxSlider);

    // ���û������Ĵ�С
    float desiredWidth = visibleSize.width - 100; // ���û������Ŀ��
    float desiredHeight = bgmSlider->getContentSize().height; // ʹ��ԭʼ�߶�
    bgmSlider->setContentSize(Size(desiredWidth, desiredHeight));
    sfxSlider->setContentSize(Size(desiredWidth, desiredHeight));

    // ����������ʾ
    bgmLabel = Label::createWithSystemFont("", "Arial", 24);
    bgmLabel->setPosition(Vec2(bgmSlider->getPositionX() + bgmSlider->getContentSize().width / 2 + 50, bgmSlider->getPositionY()));
    this->addChild(bgmLabel);

    // ����������ʾ
    sfxLabel = Label::createWithSystemFont("", "Arial", 24);
    sfxLabel->setPosition(Vec2(sfxSlider->getPositionX() + sfxSlider->getContentSize().width / 2 + 50, sfxSlider->getPositionY()));
    this->addChild(sfxLabel);

    //������ʾ
    auto BGMLabel = Label::createWithSystemFont("BGM", "Arial", 40);
    auto SFXLabel = Label::createWithSystemFont("SFX", "Arial", 40);
    BGMLabel->setPosition(Vec2(bgmSlider->getPositionX() - bgmSlider->getContentSize().width / 2-50 , bgmSlider->getPositionY()));
    SFXLabel->setPosition(Vec2(sfxSlider->getPositionX() - sfxSlider->getContentSize().width / 2-50 , sfxSlider->getPositionY()));
    this->addChild(BGMLabel);
    this->addChild(SFXLabel);
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


void Test_Scene_2::bgmSliderCallback(Ref* sender, ui::Slider::EventType eventType)
{
    if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
        int volume = slider->getPercent();

        // ���ñ�����������
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume / 100.0f);

        // ����������ʾ
        std::string labelText = "" + std::to_string(volume) + "%";
        bgmLabel->setString(labelText);
    }
}

void Test_Scene_2::sfxSliderCallback(Ref* sender, ui::Slider::EventType eventType)
{
    if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
        int volume = slider->getPercent();

        // ������Ч����
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume / 100.0f);

        // ����������ʾ
        std::string labelText = "" + std::to_string(volume) + "%";
        sfxLabel->setString(labelText);
    }
}

