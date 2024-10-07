#pragma once
#include "Command.h"

namespace GameOfLife {
	class IterateCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "iterate";
		static constexpr std::string_view Summary = "Iterate the game of life";
		static constexpr std::string_view Usage =
			"iterate [n=1]"
			"  n: Number of iterations to perform (default: 1)";

		IterateCommand(std::string_view args);

		void execute(Controller* controller) override;

	private:
		int iterations;
	};
}