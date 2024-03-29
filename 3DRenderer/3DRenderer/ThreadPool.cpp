#include "stdafx.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t _num_threads)
: num_threads(_num_threads), stop_all(false)
{
	worker_threads.reserve(num_threads);
	for (size_t i = 0; i < num_threads; i++)
		worker_threads.emplace_back([this](int i) {this->WorkerThread(i); }, i);
}

ThreadPool::~ThreadPool()
{
	stop_all = true;
	cv_job_q.notify_all();

	for (auto& i : worker_threads)
		i.join();
}

void ThreadPool::WorkerThread(const int _Number)
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(m_job_q);
		cv_job_q.wait(lock, [this]() {return !this->jobs.empty() || stop_all; });
		Thread_wait[_Number] = false;
		if (stop_all && this->jobs.empty())
		{
			Thread_wait[_Number] = true;
			return;
		}

		std::function<void()> job = std::move(jobs.front());
		jobs.pop();
		lock.unlock();

		job();
		Thread_wait[_Number] = true;
	}
}

bool ThreadPool::AllThreadWait()
{ 	
	return bool((Thread_wait[0] & Thread_wait[1] & Thread_wait[2] & Thread_wait[3]) && jobs.empty());
}