#include "Experiment.h"

#include <iostream>

#include "ExperimentRunner.h"

namespace GameOfLife::Experiment {
	std::unique_ptr<Result> Experiment::run()
	{
		for (int attempt = 0; attempt < mParameters.mMaxAttempts; attempt++)
		{
			mTasks.emplace_back(std::make_unique<ExperimentRunner>(*this, attempt));
		}
		dispatch();

		return std::move(mResult);
	}

	std::unique_ptr<ExperimentRunner> Experiment::getTask()
	{
		std::lock_guard<std::mutex> guard(mTasksLock);

		if (mTasks.empty())
			return nullptr;
		auto task = std::move(mTasks.back());
		mTasks.pop_back();
		mTotalAttempts++;

		return std::move(task);
	}

	int Experiment::getTotalAttempts()
	{
		std::lock_guard<std::mutex> guard(mTasksLock);
		return mTotalAttempts;
	}

	void Experiment::setResult(std::unique_ptr<Result> result)
	{
		{
			std::lock_guard<std::mutex> guard(mResultLock);
			mResult = std::move(result);
		}

		{
			std::lock_guard<std::mutex> guard(mTasksLock);
			mTasks.clear();
		}
	}

	void threadFunc(Experiment* experiment)
	{
		while (true)
		{
			auto task = experiment->getTask();
			if (task == nullptr)
				break;

			auto result = task->run();
			if (result != nullptr)
			{
				experiment->setResult(std::move(result));
				break;
			}
		}
	}

	void Experiment::dispatch()
	{
		// Thread creation is fairly expensive, so create a fixed number and reuse them
		// between attempts
		std::vector<std::thread> threads;

		for (int i = 0; i < mParameters.mThreads; i++)
		{
			threads.emplace_back(threadFunc, this);
		}

		for (auto& thread : threads)
		{
			thread.join();
		}
	}
}