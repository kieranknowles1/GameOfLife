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
		// TODO: Parse arguments
		// TODO: Allow setting parameters for the experiment
		if (args.empty()) {
			throw std::invalid_argument("Experiment not specified");
		}
		mExperiment = std::string(args);
	}

	void ExperimentCommand::execute(Controller* context)
	{
		std::ifstream file("./pattern/" + mExperiment + ".txt");
		std::string data(std::istreambuf_iterator<char>(file), {});

		Pattern pattern = Serializer::deserializePattern(data);

		Experiment experiment(context->getExperimentParameters(), pattern);

		experiment.run();
		auto result = experiment.getResult();

		if (result != nullptr) {
			printFinalResult(&experiment, result);
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
		for (int i = 0; i <= result->mGenerations; i++)
		{
			std::cout << board.toString() << "\n";
			board.iterate();
		}
	}
}