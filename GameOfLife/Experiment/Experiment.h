#pragma once

#include <memory>

#include "Pattern.h"

#include "../Array2D.h"

namespace GameOfLife::Experiment
{
	struct Parameters
	{
		Vec2 mBoardSize;
		int mInitialPopulation;
		int mMaxGenerations;
		int mMaxAttempts;
	};

	struct Result
	{
		static Result Failure()
		{
			return { false, 0, nullptr};
		}

		bool mSuccess;
		int mAttempts;
		std::unique_ptr<Board> mFinalBoard;
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

