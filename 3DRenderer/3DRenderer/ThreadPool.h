#pragma once

#include <thread>
#include <condition_variable>
#include <mutex>
#include <future>
#include <vector>
#include <queue>

class ThreadPool
{
private:
	size_t num_threads;
	std::vector<std::thread> worker_threads;
	std::queue<std::function<void()>> jobs;
	std::condition_variable cv_job_q;
	std::mutex m_job_q;

	bool stop_all;
	bool Thread_wait[4]{ true, true, true, true };

public:
	ThreadPool(size_t _num_threads);
	~ThreadPool();

public:	
	template<class F, class... Args>
	FORCEINLINE void EnqueueJob(F&& f, Args&&... args);	
	bool AllThreadWait() { return bool(Thread_wait[0] & Thread_wait[1] & Thread_wait[2] & Thread_wait[3]); }

private:
	void WorkerThread(const int _Number);	
};

template<class F, class... Args>
FORCEINLINE void ThreadPool::EnqueueJob(F&& f, Args&&... args)
{
	if (stop_all)
		throw std::runtime_error("ThreadPool »ç¿ë ÁßÁöµÊ");

	auto job = std::bind(std::forward<F>(f), std::forward<Args>(args)...);		
	{
		std::lock_guard<std::mutex> lock(m_job_q);
		jobs.push([job]() {job(); });
	}
	cv_job_q.notify_one();
};

