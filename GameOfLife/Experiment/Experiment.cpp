#include "Experiment.h"

#include <iostream>

namespace GameOfLife::Experiment {
	Result GameOfLife::Experiment::Experiment::run()
	{
		for (int attempt = 0; attempt < mParameters.mMaxAttempts; attempt++)
		{
			// TODO: Use multitiple threads, each doing a single attempt at a time
			auto result = runSingleAttempt(attempt);
			if (result.mSuccess)
				return result;
		}
		return Result::Failure();
	}
	Result Experiment::runSingleAttempt(int attempt)
	{
		std::cout << "Starting attempt " << attempt << "\n";
		// Seed the random number generator with the attempt number
		std::mt19937 rng(attempt);

		// Create a new board
		auto board = Board(mParameters.mBoardSize);
		board.fillRandom(mParameters.mInitialPopulation, rng);

		// Run the game of life for mMaxGenerations generations
		for (int generation = 0; generation < mParameters.mMaxGenerations; generation++)
		{
			board.iterate();
			// TODO: Find any patterns on their first frame, track
			// these as candidates, and return success if any of them
			// survive long enough
		}

		return Result::Failure();
	}
}