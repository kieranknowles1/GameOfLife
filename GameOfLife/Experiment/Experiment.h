#pragma once

#include <memory>
#include <vector>
#include <thread>
#include <mutex>
#include <map>

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

		// Get the efficiency resource number of an experiment with these parameters
		// Defined as the sum of the board size and the initial population
		int getEfficiencyResourceNumber() const
		{
			return mBoardSize.x + mBoardSize.y + mInitialPopulation;
		}

		std::map<std::string_view, int*> getValuesMap()
		{
			return std::map<std::string_view, int*>{
				{ "width", &mBoardSize.x },
				{ "height", &mBoardSize.y },
				{ "population", &mInitialPopulation },
				{ "generations", &mMaxGenerations },
				{ "attempts", &mMaxAttempts },
				{ "lifetime", &mMinimumLifetime },
				{ "threads", &mThreads }
			};
		}
	};

	class Experiment
	{
	public:
		Experiment(Parameters parameters, std::vector<Pattern>& targetPatterns)
			: mParameters(parameters)
			, mTargetPatterns(targetPatterns)
		{
		}

		std::unique_ptr<Result> run();

		const Parameters& getParameters() const { return mParameters; }
		const std::vector<Pattern>& getTargetPatterns() const { return mTargetPatterns; }

		// Get the next task to run and pop it from the list
		// Returns nullptr if there are no more tasks
		// Thread safe
		std::unique_ptr<ExperimentRunner> getTask();

		// Get the total number of attempts that have been run
		// Locks the task list
		int getTotalAttempts();

		// Set the result of the experiment, and cancel all other tasks
		// Thread safe
		void setResult(std::unique_ptr<Result> result);
	private:
		// Start all threads and wait for them to finish
		void dispatch();

		std::mutex mTasksLock;
		std::vector<std::unique_ptr<ExperimentRunner>> mTasks;
		int mTotalAttempts = 0;

		std::mutex mResultLock;
		std::unique_ptr<Result> mResult;

		Parameters mParameters;
		std::vector<Pattern> mTargetPatterns;
	};
}

