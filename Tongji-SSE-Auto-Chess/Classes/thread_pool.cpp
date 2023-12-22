#include<iostream>
#include<thread>
#include<queue>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<functional>

#define default_thread_num 10

class thread_pool {
public:
	static thread_pool& getInstance() {
		static thread_pool ThreadPool(default_thread_num);
		return ThreadPool;
	}

	template<class F, class... Args>
	void enqueue(F&& f, Args&&... args) {       //ͨ������
		std::function<void()>task =
			std::bind(std::forward<F>(f), std::forward<Args>(args...)); //ͨ������ת��ʵ��ͨ������
		std::unique_lock<std::mutex> lock(mtx);
		tasks.emplace(std::move(task));
		condition.notify_one();                //֪ͨ����һ������
	}

	void set_stop(int status=true) {
		stop = status;
	}
private:
	thread_pool(int numThreads) :stop(false) {
		for (int i = 0; i < numThreads; i++) {
			//push_back�ǲ��ÿ����������������emplace_back�ǵ��ù��캯��ֱ�ӹ���һ���µļ���
			threads.emplace_back([this] {
				while (1) {
					std::unique_lock<std::mutex> lock(mtx);
					condition.wait(lock, [this] {
						return !tasks.empty() && stop;
						});

					if (stop&&tasks.empty()) {
						return;
					}

					std::function<void()> task(std::move(tasks.front()));
					tasks.pop();
					lock.unlock();
					task();
				}
				});
		}
	}

	~thread_pool() {
		{
			std::unique_lock<std::mutex> lock(mtx);
			set_stop();
		}
		condition.notify_all();          //֪ͨ����������ȡ��
		for (auto& t : threads) {
			t.join();
		}
	}

	std::vector<std::thread> threads;           //�̶߳���
	std::queue<std::function<void()>> tasks;    //�������

	std::mutex mtx;                    //������
	std::condition_variable condition; //��������

	bool stop;   //�̳߳���ֹ����
};