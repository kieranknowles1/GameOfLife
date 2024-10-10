#pragma once

#include "../Board.h"

namespace GameOfLife::Experiment {
	class Experiment;

	struct Result
	{
		Result(int seed, int generations, Board& finalBoard)
			: mSeed(seed)
			, mGenerations(generations)
			, mFinalBoard(finalBoard)
		{}

		int mSeed;
		int mGenerations;
		Board mFinalBoard;
	};

	class ExperimentRunner {
	public:
		ExperimentRunner(const Experiment& experiment, int seed);

		std::unique_ptr<Result> run();

	private:
		const Experiment& mExperiment;
		int mSeed;
	};
}