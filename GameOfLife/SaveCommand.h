#pragma once

#include "Command.h"

namespace GameOfLife {
	class SaveCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "save";
		static constexpr std::string_view Summary = "Save the current board to a file";
		static constexpr std::string_view Usage =
			"save <filename>\n"
			"  filename: The name of the file to save the board to\n";

		SaveCommand(std::string_view args);

		void execute(Controller* controller) override;
	private:
		std::string mFilename;
	};
}