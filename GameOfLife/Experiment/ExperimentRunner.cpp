#include "ExperimentRunner.h"

#include <iostream>

#include "Experiment.h"

namespace GameOfLife::Experiment {
	struct Candidate
	{
		Vec2 mPosition;
		int mCurrentLifetime;
	};

	ExperimentRunner::ExperimentRunner(const Experiment& experiment, int seed)
		: mExperiment(experiment)
		, mSeed(seed)
	{
	}

	Result ExperimentRunner::run()
	{
		auto& params = mExperiment.getParameters();
		auto& pattern = mExperiment.getTargetPattern();

		// TODO: Remove cout
		std::cout << "Starting attempt with seed " << mSeed << "\n";
		// Seed the random number generator with the attempt number
		std::mt19937 rng(mSeed);

		// Create a new board
		auto board = Board(params.mBoardSize);
		board.fillRandom(params.mInitialPopulation, rng);

		std::vector<Candidate> candidates;

		// Run the game of life for mMaxGenerations generations
		for (int generation = 0; generation < params.mMaxGenerations; generation++)
		{
			// Check that our candidates are still alive
			for (int i = 0; i < candidates.size(); i++)
			{
				auto& candidate = candidates[i];
				auto frame = candidate.mCurrentLifetime;
				bool alive = pattern.existsAtPosition(board, candidate.mPosition, frame);
				if (alive)
				{
					candidate.mCurrentLifetime++;
					if (candidate.mCurrentLifetime >= params.mMinimumLifetime)
						return Result{ true, mSeed, generation, std::make_unique<Board>(board) };
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
			auto found = pattern.findInstances(board);
			for (auto& item : found)
			{
				// The first frame has already been seen, we will
				// look at frame 2 next
				candidates.emplace_back(Candidate{ item, 1 });
			}

			board.iterate();
		}

		return Result::Failure();
	}
}