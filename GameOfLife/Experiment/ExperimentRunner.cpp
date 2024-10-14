#include "ExperimentRunner.h"

#include "Experiment.h"

namespace GameOfLife::Experiment {
	bool Candidate::isAlive(const Board& board) const
	{
		return mPattern->existsAtPosition(board, mPosition, mCurrentLifetime);
	}

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
				if (candidate.isAlive(board) || mExperiment.getParameters().mMinimumLifetime < 2)
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

			findCandidates(board, candidates);

			board.iterate();
		}

		return nullptr;
	}

	void ExperimentRunner::findCandidates(const Board& board, std::vector<Candidate>& out)
	{
		for (auto& pattern : mExperiment.getTargetPatterns())
		{
			auto found = pattern.findInstances(board);
			for (auto& item : found)
			{
				out.emplace_back(&pattern, item);
			}
		}
	}
}