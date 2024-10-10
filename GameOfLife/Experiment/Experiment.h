#pragma once

#include <memory>

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

		Result run();

		const Parameters& getParameters() const { return mParameters; }
		const Pattern& getTargetPattern() const { return mTargetPattern; }
	private:
		// Start all threads and wait for them to finish
		Result dispatch();

		std::vector<ExperimentRunner> mTasks;

		Parameters mParameters;
		Pattern mTargetPattern;
	};
}

