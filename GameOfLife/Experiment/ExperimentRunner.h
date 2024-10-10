#pragma once

#include "../Board.h"

namespace GameOfLife::Experiment {
	class Experiment;

	struct Result
	{
		static Result Failure()
		{
			return { false, 0, 0, nullptr };
		}

		bool mSuccess;
		int mAttempts;
		int mGenerations;
		std::unique_ptr<Board> mFinalBoard;
	};

	class ExperimentRunner {
	public:
		ExperimentRunner(const Experiment& experiment, int seed);

		Result run();

	private:
		const Experiment& mExperiment;
		int mSeed;
	};
}