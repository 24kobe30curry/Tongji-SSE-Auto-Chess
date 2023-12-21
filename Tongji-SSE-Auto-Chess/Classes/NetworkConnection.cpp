#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace network;

class TimeSaveManager {
public:
    static TimeSaveManager* getInstance() {
        static TimeSaveManager instance;
        return &instance;
    }

    // ����GET�����ȡ�û���ʱ��浵����
    void getTimeSave(const std::string& userId) {
        HttpRequest* request = new HttpRequest();
        request->setUrl(StringUtils::format("http://localhost:3000/get-time-save/%s", userId.c_str()));
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(TimeSaveManager::onGetTimeSaveResponse, this));
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // ����POST��������û���ʱ��浵����
    void updateTimeSave(const std::string& userId, int newTimeSave) {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://localhost:3000/update-time-save");
        request->setRequestType(HttpRequest::Type::POST);
        request->setResponseCallback(CC_CALLBACK_2(TimeSaveManager::onUpdateTimeSaveResponse, this));

        // �����������
        std::string postData = StringUtils::format("userId=%s&timeSave=%d", userId.c_str(), newTimeSave);
        request->setRequestData(postData.c_str(), postData.size());

        // ��������
        HttpClient::getInstance()->send(request);
        request->release();
    }

private:
    // ����GET����Ļص�
    void onGetTimeSaveResponse(HttpClient* client, HttpResponse* response) {
        if (!response || !response->isSucceed()) {
            CCLOG("Get Time Save Request failed");
            return;
        }

        // �����������Ӧ�����ݣ�������Խ���JSON�ȸ�ʽ
        std::vector<char>* buffer = response->getResponseData();
        std::string responseData(buffer->begin(), buffer->end());
        CCLOG("Get Time Save Response: %s", responseData.c_str());
        // �����ﴦ���������Ӧ������
    }

    // ����POST����Ļص�
    void onUpdateTimeSaveResponse(HttpClient* client, HttpResponse* response) {
        if (!response || !response->isSucceed()) {
            CCLOG("Update Time Save Request failed");
            return;
        }

        // �����������Ӧ�����ݣ�������Խ���JSON�ȸ�ʽ
        std::vector<char>* buffer = response->getResponseData();
        std::string responseData(buffer->begin(), buffer->end());
        CCLOG("Update Time Save Response: %s", responseData.c_str());
        // �����ﴦ���������Ӧ������
    }
};
