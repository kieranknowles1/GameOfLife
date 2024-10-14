#pragma once

#include "../Board.h"

namespace GameOfLife::Experiment {
	class Experiment;

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

		bool isAlive(const Board& board) const;
	};

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
		void findCandidates(const Board& board, std::vector<Candidate>& out);

		const Experiment& mExperiment;
		int mSeed;
	};
}