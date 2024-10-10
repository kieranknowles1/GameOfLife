#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <mutex>

#include "Pattern.h"
#include "ExperimentRunner.h"

#include "../Array2D.h"

namespace GameOfLife::Experiment
{
	struct Parameters
	{
		// The size of the board
		Vec2 mBoardSize;
		// The number of cells to start with
		int mInitialPopulation;
		// The number of generations to run each attempt
		int mMaxGenerations;
		// The number of attempts to run the experiment
		int mMaxAttempts;
		// How long the pattern must survive for the experiment to be considered a success
		int mMinimumLifetime;
		// The number of threads to use
		int mThreads;
	};

	class Experiment
	{
	public:
		Experiment(Parameters parameters, Pattern targetPattern)
			: mParameters(parameters)
			, mTargetPattern(targetPattern)
		{
		}

		void run();

		const Parameters& getParameters() const { return mParameters; }
		const Pattern& getTargetPattern() const { return mTargetPattern; }

		// Get the next task to run and pop it from the list
		// Returns nullptr if there are no more tasks
		// Thread safe
		std::unique_ptr<ExperimentRunner> getTask();

		// Set the result of the experiment, and cancel all other tasks
		// Thread safe
		void setResult(std::unique_ptr<Result> result);

		// Get a non-owning pointer to the result of the experiment
		// or nullptr if the experiment failed
		Result* getResult() { return mResult.get(); }
	private:
		// Start all threads and wait for them to finish
		void dispatch();

		std::mutex mTasksLock;
		std::vector<std::unique_ptr<ExperimentRunner>> mTasks;

		std::mutex mResultLock;
		std::unique_ptr<Result> mResult;

		Parameters mParameters;
		Pattern mTargetPattern;
	};
}

