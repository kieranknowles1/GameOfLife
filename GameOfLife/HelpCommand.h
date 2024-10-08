#pragma once

#include "Command.h"

namespace GameOfLife {
	class HelpCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "help";
		static constexpr std::string_view Summary = "Show available commands or a specific command's usage";
		static constexpr std::string_view Usage =
			"help [command]\n"
			"List all available commands\n"
			"  [command] - Optional: Command to show detailed help for\n";

		HelpCommand(std::string_view input);

		void execute(Controller* context) override;

	private:
		// Optional: Command to show help for
		std::string mCommand;
	};
}