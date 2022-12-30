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

public:
	ThreadPool(size_t _num_threads);
	~ThreadPool();

public:
	//template<class F, class... Args>
	//std::future<std::invoke_result_t<F, Args...>> EnqueueJob(F&& f, Args&&... args);
	template<class F, class... Args>
	FORCEINLINE void EnqueueJob(F&& f, Args&&... args);

private:
	void WorkerThread();
};

template<class F, class... Args>
FORCEINLINE void ThreadPool::EnqueueJob(F&& f, Args&&... args)
{
	if (stop_all)
		throw std::runtime_error("ThreadPool ��� ������");

	auto job = std::bind(std::forward<F>(f), std::forward<Args>(args)...);		
	{
		std::lock_guard<std::mutex> lock(m_job_q);
		jobs.push([job]() {job(); });
	}
	cv_job_q.notify_one();
};

/* future ��ü �ۼ� ��������, �����ʿ�(���ϰ� ȹ�氡���� �Լ�����)
template<class F, class... Args>
FORCEINLINE std::future<std::invoke_result_t<F, Args...>> ThreadPool::EnqueueJob(
	F&& f, Args&&... args)
{ 	
	if (stop_all)
		throw std::runtime_error("ThreadPool ��� ������");
	
	using return_type = std::invoke_result<F, Args...>::type;	
	
	auto job = std::make_shared<std::packaged_task<return_type()>>(
	std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	//auto job = std::make_shared<std::packaged_task<return_type()>>(
	//	[&args...]() { f(std::forward<Args>(args)...); });
	
	std::future<return_type> job_result_future = job->get_future();
	{
		std::lock_guard<std::mutex> lock(m_job_q);
		jobs.push([job]() {(*job)(); });
	}
	cv_job_q.notify_one();
	return job_result_future;			
}
*/