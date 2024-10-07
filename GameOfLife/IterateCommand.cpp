#include "IterateCommand.h"

#include "Controller.h"

namespace GameOfLife {
	IterateCommand::IterateCommand(std::string_view args)
	{
		// Parse the number of iterations from the arguments
		iterations = 1;
		if (!args.empty())
		{
			// Throws if the string is not a valid number
			iterations = std::stoi(std::string(args));
		}
	}

	void IterateCommand::execute(Controller* controller)
	{
		auto board = controller->getBoard();

		if (board == nullptr)
		{
			throw std::runtime_error("No board loaded");
		}

		for (int i = 0; i < iterations; i++)
		{
			board->iterate();
		}
	}
}