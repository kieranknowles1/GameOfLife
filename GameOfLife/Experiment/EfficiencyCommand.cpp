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

		// The ERN that would come from placing the pattern directly in the top left corner
		// This will be the worst case scenario and an upper bound for our tests
		int bruteForceErn = pattern.getCellCount() + pattern.getSize().x + pattern.getSize().y;

		auto result = runTests(pattern, bruteForceErn);

		
		printFinalResult(&result, &pattern);
	}

	static int ern(int width = 0, int height = 0, int cells = 0)
	{
		return cells + width + height;
	}

	EfficiencyResult EfficiencyCommand::runTests(Pattern& pattern, int bruteForceErn)
	{
		std::vector<Pattern> patternVec{ pattern };

		int bestResourceNumber = bruteForceErn;
		std::unique_ptr<Result> best = nullptr;

		for (int width = pattern.getSize().x; ern(width) < bestResourceNumber; width++)
		{
			for (int height = pattern.getSize().y; ern(width, height) < bestResourceNumber; height++)
			{
				for (int cells = MinPossibleCells; ern(width, height, cells) < bestResourceNumber; cells++)
				{
					Parameters params{
						{ width, height },
						cells,
						50, // Max generations, pattern should be apparent by then
						10000, // Max attempts
						1, // Minimum lifetime
						6, // Threads
					};

					auto result = attemptExperiment(patternVec, params);

					if (result != nullptr) {
						return {
							params,
							std::move(result)
						};
					}
				}
			}
		}

		return {
			Parameters{},
			nullptr
		};
	}


	std::unique_ptr<Result> EfficiencyCommand::attemptExperiment(std::vector<Pattern>& patterns, Parameters& params)
	{
		Experiment experiment(params, patterns);

		return experiment.run();
	}

	void EfficiencyCommand::printFinalResult(EfficiencyResult* result, Pattern* pattern)
	{
		auto experimentResult = result->result.get();

		if (experimentResult == nullptr) {
			std::cout << "Best ERN appears to be brute force: ERN = " << ern(pattern->getSize().x, pattern->getSize().y, pattern->getCellCount()) << "\n";
			std::cout << pattern->getFrame(0).getCells().serializeBody() << "\n";
		}
		else {
			std::cout << "ERN: " << result->params.getEfficiencyResourceNumber() << "\n";
			std::cout << experimentResult->mFinalBoard.getSize().x << " " << experimentResult->mFinalBoard.getSize().y << "\n";
			std::cout << "Seed: " << experimentResult->mSeed << "\n";

			// Get a board based on the initial cells of the final board
			Board board(experimentResult->mFinalBoard.getInitialCells());
			for (int i = 0; i <= experimentResult->mGenerations; i++)
			{
				std::cout << board.toString() << "\n";
				board.iterate();
			}
		}
	}
}