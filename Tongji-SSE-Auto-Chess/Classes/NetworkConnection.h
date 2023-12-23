#pragma once
//#include "cocos2d.h"
//#include "network/HttpClient.h"
//
//USING_NS_CC;
//using namespace network;
//
//class NetworkManager {
//public:
//    static NetworkManager* getInstance() {
//        static NetworkManager instance;
//        return &instance;
//    }
//
//    void checkNetworkConnection() {
//        HttpRequest* request = new HttpRequest();
//        request->setUrl("http://www.google.com");
//        request->setRequestType(HttpRequest::Type::GET);
//        request->setResponseCallback(CC_CALLBACK_2(NetworkManager::onNetworkCheckResponse, this));
//        HttpClient::getInstance()->send(request);
//        request->release();
//    }
//
//private:
//    void onNetworkCheckResponse(HttpClient* client, HttpResponse* response) {
//        if (response && response->isSucceed()) {
//            CCLOG("Network is connected");
//            // ������ִ�����ӳɹ�����߼�
//        }
//        else {
//            CCLOG("Network is not connected");
//            // ������ִ������ʧ�ܺ���߼�
//        }
//    }
//};
//
//class HelloWorld : public cocos2d::Scene {
//public:
//    virtual bool init() {
//        if (!Scene::init()) {
//            return false;
//        }
//
//        // ʹ�� NetworkManager �����������
//        NetworkManager::getInstance()->checkNetworkConnection();
//
//        return true;
//    }
//
//    CREATE_FUNC(HelloWorld);
//};
//
//int main(int argc, char** argv) {
//    auto director = cocos2d::Director::getInstance();
//    auto glview = director->getOpenGLView();
//
//    if (!glview) {
//        glview = cocos2d::GLViewImpl::create("My Cocos Game");
//        director->setOpenGLView(glview);
//    }
//
//    auto scene = HelloWorld::create();
//    director->runWithScene(scene);
//
//    return 0;
//}
