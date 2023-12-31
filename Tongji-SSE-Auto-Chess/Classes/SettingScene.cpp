//#include <goldenshovel_hero_design.h>
#include "HelloWorldScene.h"
#include "SettingScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* SettingScene::createScene()
{
    return SettingScene::create();
}

bool SettingScene::init()
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
    bgmSlider->addEventListener(CC_CALLBACK_2(SettingScene::bgmSliderCallback, this));
    this->addChild(bgmSlider,1);

    // ������Ч�����������ؼ�
    auto sfxSlider = ui::Slider::create();
    sfxSlider->loadBarTexture("slider_progress.png");
    sfxSlider->loadSlidBallTextures("slider_ball.png", "slider_ball.png", "");
    sfxSlider->loadProgressBarTexture("slider_progress.png");
    sfxSlider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    sfxSlider->addEventListener(CC_CALLBACK_2(SettingScene::sfxSliderCallback, this));
    this->addChild(sfxSlider,1);

    // ���û������Ĵ�С
    float desiredWidth = visibleSize.width - 100; // ���û������Ŀ��
    float desiredHeight = bgmSlider->getContentSize().height; // ʹ��ԭʼ�߶�
    bgmSlider->setContentSize(Size(desiredWidth, desiredHeight));
    sfxSlider->setContentSize(Size(desiredWidth, desiredHeight));

    // ����������ʾ
    bgmLabel = Label::createWithSystemFont("", "Arial", 24);
    bgmLabel->setPosition(Vec2(bgmSlider->getPositionX() + bgmSlider->getContentSize().width / 2 + 50, bgmSlider->getPositionY()));
    this->addChild(bgmLabel,1);

    // ����������ʾ
    sfxLabel = Label::createWithSystemFont("", "Arial", 24);
    sfxLabel->setPosition(Vec2(sfxSlider->getPositionX() + sfxSlider->getContentSize().width / 2 + 50, sfxSlider->getPositionY()));
    this->addChild(sfxLabel,1);

    //������ʾ
    auto BGMLabel = Label::createWithSystemFont("BGM", "Arial", 40);
    auto SFXLabel = Label::createWithSystemFont("SFX", "Arial", 40);
    BGMLabel->setPosition(Vec2(bgmSlider->getPositionX() - bgmSlider->getContentSize().width / 2-60 , bgmSlider->getPositionY()));
    SFXLabel->setPosition(Vec2(sfxSlider->getPositionX() - sfxSlider->getContentSize().width / 2-60 , sfxSlider->getPositionY()));
    this->addChild(BGMLabel,1);
    this->addChild(SFXLabel,1);

    auto sprite = Sprite::create("board.png");
    sprite->setPosition(Vec2(visibleSize.width/2-50,visibleSize.height/2+50));
    this->addChild(sprite,0);
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

void SettingScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}


void SettingScene::bgmSliderCallback(Ref* sender, ui::Slider::EventType eventType)
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

void SettingScene::sfxSliderCallback(Ref* sender, ui::Slider::EventType eventType)
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

