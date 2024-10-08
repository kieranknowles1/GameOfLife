#pragma once

#include <memory>

#include "Board.h"
#include "Command.h"
#include "CommandParser.h"

namespace GameOfLife
{
	class Controller
	{
	public:
		Controller(std::unique_ptr<CommandParser> parser) :
			mParser(std::move(parser)),
			mQuitRequested(false)
		{}

		// Run the controller until the user quits
		void run();

		// Request the controller to quit at the next opportunity
		void requestQuit() { mQuitRequested = true; }

		// .get() returns a non-owning pointer, similar to borrowing in Rust
		CommandParser* getParser() { return mParser.get(); }

		void setBoard(std::unique_ptr<Board> board) { mBoard = std::move(board); }
		Board* getBoard() { return mBoard.get(); }

		std::string_view getSaveDirectory() const {
			return "./save";
		}
	private:
		std::unique_ptr<CommandParser> mParser;

		std::unique_ptr<Board> mBoard;

		bool mQuitRequested = false;


		std::unique_ptr<Command> parseInput();
	};
}
