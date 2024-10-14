#include "IterateCommand.h"

#include <sstream>
#include <iostream>

#include "Controller.h"

namespace GameOfLife {
	IterateCommand::IterateCommand(std::string_view args)
		: mLoud(false)
	{
		if (args.empty())
		{
			mIterations = 1;
			return;
		}

		std::stringstream stream(args.data());

		stream >> mIterations;
		if (stream.fail())
		{
			throw std::invalid_argument("Invalid number of iterations");
		}

		// Only look if there is a space in the string
		if (args.find(' ') != std::string::npos)
		{
			stream >> std::boolalpha >> mLoud;
			if (stream.fail())
			{
				throw std::invalid_argument("Invalid loud flag");
			}
		}
	}

	void IterateCommand::execute(Controller* controller)
	{
		auto board = controller->getBoard();

		if (board == nullptr)
		{
			throw std::runtime_error("No board loaded");
		}
		board->iterate(mIterations, mLoud);
	}
}