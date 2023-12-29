#ifndef __CSOCKET_H__
#define __CSOCKET_H__
#include <windows.h>
#include "SocketEnum.h"
#include <iostream>
#include"passinfo.h"
using namespace std;

class CSocket
{
public:
	CSocket(SocketEnum::SocketType _socketType = SocketEnum::Tcp);
	~CSocket();
	bool Connect(const char* ip, int port);		//���� 
	int Send(passinfo* passInfo, int len);	//����
	int Send();	//����
	int Receive(int strLen);	//����
	bool SetBlocking(bool isBlocking);//��������ģʽ
	bool ShutDown(SocketEnum::ShutdownMode mode);
	const passinfo* GetData() const;//��ȡ��������
	SocketEnum::SocketError GetSocketError();
	passinfo* _passInfo;
	void SetSocketHandle(SOCKET socket);
	void Close();
	bool IsExit();
	//private:

	void SetSocketError(SocketEnum::SocketError error);	//���ô�����Ϣ
	void SetSocketError(void);
	bool IsSocketValid(void);
	SOCKET csocket;
	bool isConnected;	//����״̬
	struct sockaddr_in serverAddress;
	int sendCount;	//�������ݳ���
	int recvCount;	//�������ݳ���
	bool isBlocking;	//�Ƿ�������ģʽ
	SocketEnum::SocketError socketError;
	SocketEnum::SocketType socketType;
	WSADATA wsa;
};

#endif