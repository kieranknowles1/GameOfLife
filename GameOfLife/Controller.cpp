#include "Controller.h"

#include <iostream>

namespace GameOfLife
{
	void Controller::run()
	{
		while (!mQuitRequested)
		{
			auto input = parseInput();
			input->execute(this);
		}
	}

	Command* Controller::parseInput()
	{
		std::cout << "Enter a command, or type 'help' for a list of commands" << std::endl;
		std::string line;
		std::getline(std::cin, line);

		return mParser.parseInput(line);
	}
}