#pragma once

#include "Command.h"

namespace GameOfLife {
	class HelpCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "help";

		HelpCommand(std::string_view input) {}

		void execute(Controller* context) override;

	private:
		// Optional: Command to show help for
		// TODO: Implement
		std::string mCommand;
	};
}