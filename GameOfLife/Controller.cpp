#include "Controller.h"

#include <iostream>

namespace GameOfLife
{
	void Controller::run()
	{
		while (!mQuitRequested)
		{
			auto command = getCommand();
			executeCommand(command.get());
		}
	}

	std::unique_ptr<Command> Controller::getCommand()
	{
		while (true)
		{
			try {
				return parseInput();
			}
			catch (std::invalid_argument& e) {
				std::cerr << e.what() << std::endl;
				std::cerr << "Type 'help' for a list of commands" << std::endl;
			}
		}
	}

	void Controller::executeCommand(Command* command)
	{
		try {
			command->execute(this);
		}
		catch (std::exception& e) {
			std::cerr << "An error occurred: " << e.what() << std::endl;
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