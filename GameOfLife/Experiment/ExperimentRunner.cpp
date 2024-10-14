#include "ExperimentRunner.h"

#include "Experiment.h"

namespace GameOfLife::Experiment {
	struct Candidate
	{
		Candidate(const Pattern* pattern, Vec2 position)
			: mPattern(pattern)
			, mPosition(position)
			, mCurrentLifetime(1) // Already seen the first frame
		{}

		const Pattern* mPattern;
		Vec2 mPosition;
		int mCurrentLifetime;
	};

	ExperimentRunner::ExperimentRunner(const Experiment& experiment, int seed)
		: mExperiment(experiment)
		, mSeed(seed)
	{
	}

	std::unique_ptr<Result> ExperimentRunner::run()
	{
		auto& params = mExperiment.getParameters();
		auto& patterns = mExperiment.getTargetPatterns();

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
				bool alive = candidate.mPattern->existsAtPosition(board, candidate.mPosition, frame);
				if (alive || mExperiment.getParameters().mMinimumLifetime < 2)
				{
					candidate.mCurrentLifetime++;
					if (candidate.mCurrentLifetime >= params.mMinimumLifetime)
						return std::make_unique<Result>(mSeed, generation, board);
				}
				else
				{
					candidates.erase(candidates.begin() + i);
					// We've removed an item, so we need to decrement i
					i--;
				}
			}

			for (auto& pattern : patterns) {
				auto found = pattern.findInstances(board);
				for (auto& item : found)
				{
					candidates.emplace_back(&pattern, item);
				}
			}

			board.iterate();
		}

		return nullptr;
	}
}