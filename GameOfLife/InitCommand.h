#pragma once

#include "Command.h"

namespace GameOfLife {
	class InitCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "init";
		static constexpr std::string_view Summary = "Initialize the game board";
		static constexpr std::string_view Usage = 
			"init <width> <height> <alive_cells>\n"
			"Initialize the game board\n"
			"  <width> - Width of the board\n"
			"  <height> - Height of the board\n"
			"  <alive_cells> - Number of alive cells to start with\n";

		InitCommand(std::string_view input);

		void execute(Controller* context) override;
	private:
		int mWidth;
		int mHeight;
		int mAliveCells;
	};
}