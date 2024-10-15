#include "IterateCommand.h"

#include <sstream>
#include <iostream>

#include "Controller.h"
#include "Checks.h"

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
		Checks::streamOk(stream, "Invalid number of iterations");

		// Only look if there is a space in the string
		if (args.find(' ') != std::string::npos)
		{
			stream >> std::boolalpha >> mLoud;
			Checks::streamOk(stream, "Invalid loud flag");
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