#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t _num_threads)
: num_threads(_num_threads), stop_all(false)
{
	worker_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++)
		worker_threads.emplace_back([this]() {this->WorkerThread(); });
}

ThreadPool::~ThreadPool()
{
	stop_all = true;
	cv_job_q.notify_all();

	for (auto& i : worker_threads)
		i.join();
}

void ThreadPool::WorkerThread()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_job_q);
		cv_job_q.wait(lock, [this]() {return !this->jobs.empty() || stop_all; });
		
		if (stop_all && this->jobs.empty())
		{
			return;
		}

		std::function<void()> job = std::move(jobs.front());
		jobs.pop();
		lock.unlock();

		job();
	}
}
