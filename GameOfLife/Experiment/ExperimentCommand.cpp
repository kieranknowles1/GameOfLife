#include "ExperimentCommand.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cassert>

#include "../Controller.h"
#include "../Serializer.h"

#include "ExperimentRunner.h"

namespace GameOfLife::Experiment
{
	ExperimentCommand::ExperimentCommand(std::string_view args)
	{
		if (args.empty()) {
			throw std::invalid_argument("Experiment not specified");
		}

		std::stringstream ss(args.data());
		std::string item;

		while (std::getline(ss, item, ' ')) {
			mExperiment.push_back(item);
		}
	}

	void ExperimentCommand::execute(Controller* context)
	{
		std::vector<Pattern> patterns;
		for (const auto& experiment : mExperiment)
		{
			std::ifstream file("./pattern/" + experiment + ".txt");
			if (!file.good())
				throw std::runtime_error("Pattern not found: " + experiment);
			std::string data(std::istreambuf_iterator<char>(file), {});

			Pattern pattern = Serializer::deserializePattern(data);
			patterns.push_back(pattern);
		}

		Experiment experiment(context->getExperimentParameters(), patterns);

		auto result = experiment.run();

		if (result != nullptr) {
			printFinalResult(&experiment, result.get());
			context->setBoard(std::make_unique<Board>(result->mFinalBoard));
		}
		else
			std::cout << "Experiment failed\n";
	}
	void ExperimentCommand::printFinalResult(Experiment* experiment, Result* result)
	{
		std::cout << "Success after " << experiment->getTotalAttempts() << " attempts\n";
		std::cout << "Final attempt took " << result->mGenerations << " generations\n";

		// Get a board based on the initial cells of the final board
		Board board(result->mFinalBoard.getInitialCells());
		board.iterate(result->mGenerations, true);
	}
}
