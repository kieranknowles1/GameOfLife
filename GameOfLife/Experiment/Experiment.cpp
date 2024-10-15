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

		// We create mThreads threads, each of which will run the threadFunc function
		// threadFunc gets a task, runs it, then loops until there is nothing left to do
		// If the desired result is found, all remaining tasks are cancelled which causes threads to exit at the end of their current task
		// This acts as a simple thread pool, where threads are reused between attempts but not between experiments
		// ExperimentRunner has read-only access to outside data, so is inherently thread-safe as long as said data is not modified (which is the case here)
		// Note that even something as simple as this has a race condition if multiple threads are running experiments that will succeed, as the first one to finish
		// will be considered the winner, making the whole thing non-deterministic.

		// Determinism is not a requirement here, so this is fine but it would be a concern if we needed stable results. For example:
		// - the game Factoio is deterministic, in multiplayer all clients have a full copy of the game state and run the same simulation
		//   if something was non-deterministic, the game would desync between clients.
		// - Nix builds are supposed to be deterministic, if a build is not exactly reproducible then it would break the rule that a configuration is a pure function of its inputs
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