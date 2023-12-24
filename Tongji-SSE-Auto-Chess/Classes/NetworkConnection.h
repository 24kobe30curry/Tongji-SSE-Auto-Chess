#include "network/HttpClient.h"

USING_NS_CC;
using namespace network;

class NetworkManager {
public:
    static NetworkManager* getInstance() {
        static NetworkManager instance;
        return &instance;
    }

    void checkNetworkConnection() {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://100.67.79.238:1986");
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(NetworkManager::onNetworkCheckResponse, this));
        HttpClient::getInstance()->send(request);
        request->release();
    }

private:
    void onNetworkCheckResponse(HttpClient* client, HttpResponse* response) {
        if (response && response->isSucceed()) {
            CCLOG("Network is connected");
            // ������ִ�����ӳɹ�����߼�
        }
        else {
            CCLOG("Network is not connected");
            // ������ִ������ʧ�ܺ���߼�
        }
    }
};