#ifndef CONCURRENT_QUEUE_H
#define CONCURRENT_QUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>

/*
* Author: Erkan Afacan
* Thread Safe Queue implementation
*/

namespace ema {

template<typename T>
class concurrent_queue {
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;

    concurrent_queue(const concurrent_queue<T>&) = delete;
    concurrent_queue<T>& operator=(const concurrent_queue<T>&) = delete;

public:
    concurrent_queue() = default;

    ~concurrent_queue() { clear(); }

	const T& front() {
		std::unique_lock<std::mutex> lck(mtx);
		return queue.front();
	}

	const T& back() {
		std::unique_lock<std::mutex> lck(mtx);
		return queue.back();
	}

    bool empty() {
		std::unique_lock<std::mutex> lck(mtx);
		return queue.empty();
	}

    size_t size() {
		std::unique_lock<std::mutex> lck(mtx);
		return queue.size();
	}

	void push(const T& val) {
		std::unique_lock<std::mutex> lck(mtx);
		queue.push(val);

		cv.notify_one();
	}

	T pop() {
		std::unique_lock<std::mutex> lck(mtx);

		auto val = std::move(queue.front());
		queue.pop();

		return val;
	}

	T wait_and_pop() {
		std::unique_lock<std::mutex> lck(mtx);
		cv.wait(lck, [&]() {
			return !queue.empty();
		});

		auto val = std::move(queue.front());
		queue.pop();

		return val;
	}

    void clear() {
		std::unique_lock<std::mutex> lck(mtx);
		while(!queue.empty()) {
			queue.pop();
		}
	}

};
}
#endif // CONCURRENT_QUEUE_H
