#include "Controller.h"

#include <iostream>

namespace GameOfLife
{
	void Controller::run()
	{
		while (!mQuitRequested)
		{
			std::unique_ptr<Command> input = nullptr;
			try {
				input = parseInput();
			}
			catch (std::invalid_argument& e) {
				// If the command is invalid, print to stderr and continue
				std::cerr << e.what() << std::endl;
				std::cerr << "Type 'help' for a list of commands" << std::endl;
				continue;
			}

			// Input is not null, as we continued in the catch block
			try {
				input->execute(this);
			} catch (std::exception& e) {
				std::cerr << "An error occurred: " << e.what() << std::endl;
			}
		}
	}

	std::unique_ptr<Command> Controller::parseInput()
	{
		std::cout << "Enter a command, or type 'help' for a list of commands" << std::endl;
		std::string line;
		std::getline(std::cin, line);

		return mParser->parseInput(line);
	}
}