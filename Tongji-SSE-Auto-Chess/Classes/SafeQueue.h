#pragma once
#ifndef __SAFE__QUEUE__H__
#define __SAFE__QUEUE__H__
#include <mutex>
#include <queue>

//����ʵ�ְ�ȫ����
template <typename T>
class SafeQueue {
private:
	std::queue<T> m_queue;
	std::mutex m_mutex;
public:
	SafeQueue() {

	}

	SafeQueue(SafeQueue& other) {
		//�������죬����õõ���ʵ��
	}

	~SafeQueue() {

	}


	bool empty() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.empty();  //���������¼���Ƿ�Ϊ��
	}

	int size() {
		std::unique_lock<std::mutex> lock(m_mutex);
		return m_queue.size();  //���������»�ȡ����
	}

	void enqueue(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.push(t);        //���������²���Ԫ��
	}

	bool dequeue(T& t) {
		std::unique_lock<std::mutex> lock(m_mutex);
		//���������µ���Ԫ��
		if (m_queue.empty()) {
			return false;
		}
		t = std::move(m_queue.front());

		m_queue.pop();
		return true;
	}
};
#endif