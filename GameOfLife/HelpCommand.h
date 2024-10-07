#pragma once

#include <iostream>

#include "Command.h"

namespace GameOfLife {
	class HelpCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "help";

		HelpCommand(std::string_view input) {}

		// TODO: Implement
		void execute() override
		{
			std::cout << "This is a help message\n";
		}

	private:
		// Optional: Command to show help for
		// TODO: Implement
		std::string mCommand;
	};
}