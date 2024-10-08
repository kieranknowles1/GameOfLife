#pragma once

#include <memory>

#include "Pattern.h"

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
	};

	struct Result
	{
		static Result Failure()
		{
			return { false, 0, 0, nullptr};
		}

		bool mSuccess;
		int mAttempts;
		int mGenerations;
		std::unique_ptr<Board> mFinalBoard;
	};

	struct Candidate
	{
		Vec2 mPosition;
		int mCurrentLifetime;
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
	private:
		Result runSingleAttempt(int attempt);

		Parameters mParameters;
		Pattern mTargetPattern;
	};
}

