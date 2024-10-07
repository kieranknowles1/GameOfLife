#pragma once

#include "Command.h"

namespace GameOfLife {
	class ShowCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "show";
		static constexpr std::string_view Summary = "Show the current state of the board";
		static constexpr std::string_view Usage = Identifier; // Nothing special to note

		// No arguments are needed for this command
		ShowCommand(std::string_view _args) {}

		void execute(Controller* controller) override;
	};
}

