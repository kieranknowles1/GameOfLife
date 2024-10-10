#include "EfficiencyCommand.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>

#include "../Controller.h"
#include "../Serializer.h"

#include "ExperimentRunner.h"

namespace GameOfLife::Experiment
{
	EfficiencyCommand::EfficiencyCommand(std::string_view args)
	{
		if (args.empty()) {
			throw std::invalid_argument("Experiment not specified");
		}

		mExperiment = std::string(args);
	}

	void EfficiencyCommand::execute(Controller* context)
	{
		std::ifstream file("./pattern/" + mExperiment + ".txt");
		if (!file.good())
			throw std::runtime_error("Pattern not found: " + mExperiment);
		std::string data(std::istreambuf_iterator<char>(file), {});

		Pattern pattern = Serializer::deserializePattern(data);
		std::vector<Pattern> patterns = { pattern };

		// It's impossible for the pattern to exist in a smaller board than its size
		Vec2 initialSize = pattern.getSize();

		Vec2 maxSize = initialSize + Vec2{ 10, 10 };

		std::unique_ptr<Result> best = nullptr;
		int bestResourceNumber = std::numeric_limits<int>::max();

		for (int x = initialSize.x; x < maxSize.x; x++)
		{
			for (int y = initialSize.y; y < maxSize.y; y++)
			{
				Vec2 size{ x, y };
				for (int cells = MinPossibleCells; cells <= MaxCells; cells++)
				{
					Parameters params{
						size,
						cells,
						50, // Max generations, pattern should be apparent by then
						10000, // Max attempts
						4, // Minimum lifetime
						6, // Threads
					};

					// There's no point in testing if the params would be less efficient than the best result already found
					if (params.getEfficiencyResourceNumber() >= bestResourceNumber)
						continue;

					auto result = attemptExperiment(patterns, params);
					if (result != nullptr)
					{
						best = std::move(result);
						bestResourceNumber = params.getEfficiencyResourceNumber();
					}
				}
			}
		}

		if (best != nullptr)
			printFinalResult(best.get(), bestResourceNumber);
		else
			std::cout << "No result found\n";
	}

	std::unique_ptr<Result> EfficiencyCommand::attemptExperiment(std::vector<Pattern>& patterns, Parameters& params)
	{
		Experiment experiment(params, patterns);

		return experiment.run();
	}

	void EfficiencyCommand::printFinalResult(Result* result, int ern)
	{
		std::cout << "ERN: " << ern << "\n";
		std::cout << result->mFinalBoard.getSize().x << " " << result->mFinalBoard.getSize().y << "\n";
		std::cout << "Seed: " << result->mSeed << "\n";

		// Get a board based on the initial cells of the final board
		Board board(result->mFinalBoard.getInitialCells());
		for (int i = 0; i <= result->mGenerations; i++)
		{
			std::cout << board.toString() << "\n";
			board.iterate();
		}
	}
}