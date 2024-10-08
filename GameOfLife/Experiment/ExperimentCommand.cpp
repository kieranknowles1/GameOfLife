#include "ExperimentCommand.h"

#include <iostream>
#include <stdexcept>
#include <cassert>

#include "../Controller.h"

namespace GameOfLife::Experiment
{
	ExperimentCommand::ExperimentCommand(std::string_view args)
	{
		// TODO: Parse arguments
		// TODO: Allow selecting an experiment and loading from disk

		mParameters = {
			{30, 30},
			100,
			100,
			100,
			10
		};
	}

	void ExperimentCommand::execute(Controller* context)
	{
		// TODO: Load the pattern
		Pattern pattern;

		Experiment experiment(mParameters, pattern);

		auto result = experiment.run();

		if (result.mSuccess)
			printFinalResult(result);
		else
			std::cout << "Experiment failed\n";

		context->setBoard(std::move(result.mFinalBoard));
	}
	void ExperimentCommand::printFinalResult(Result& result)
	{
		assert(result.mSuccess && "Result must be a success to print");

		std::cout << "Success on attempt " << result.mAttempts << "\n";
		std::cout << "Final attempt took " << result.mGenerations << " generations\n";

		// Get a board based on the initial cells of the final board
		Board board(result.mFinalBoard->getInitialCells());
		for (int i = 0; i <= result.mGenerations; i++)
		{
			std::cout << board.toString() << "\n";
			board.iterate();
		}
	}
}