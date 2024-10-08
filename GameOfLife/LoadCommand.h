#pragma once

#include "Command.h"


namespace GameOfLife {
	class LoadCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "load";
		static constexpr std::string_view Summary = "Load a board from a file";
		static constexpr std::string_view Usage = "load <filename>";

		LoadCommand(std::string_view args);

		void execute(Controller* controller) override;

	private:
		std::string mFilename;
	};
}