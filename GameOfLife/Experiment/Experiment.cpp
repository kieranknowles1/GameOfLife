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

		std::vector<Candidate> candidates;

		// Run the game of life for mMaxGenerations generations
		for (int generation = 0; generation < mParameters.mMaxGenerations; generation++)
		{
			// Check that our candidates are still alive
			for (int i = 0; i < candidates.size(); i++)
			{
				auto& candidate = candidates[i];
				auto frame = candidate.mCurrentLifetime;
				bool alive = mTargetPattern.existsAtPosition(board, candidate.mPosition, frame);
				if (alive)
				{
					candidate.mCurrentLifetime++;
					if (candidate.mCurrentLifetime >= mParameters.mMinimumLifetime)
						return Result{ true, attempt, generation, std::make_unique<Board>(board) };
				}
				else
				{
					candidates.erase(candidates.begin() + i);
					// We've removed an item, so we need to decrement i
					i--;
				}
			}

			// TODO: Find any patterns on their first frame, track
			// these as candidates, and return success if any of them
			// survive long enough
			auto found = mTargetPattern.findInstances(board);
			for (auto& item : found)
			{
				candidates.emplace_back(Candidate{ item, 0 });
			}

			board.iterate();
		}

		return Result::Failure();
	}
}