#pragma once

#include <memory>

#include "Board.h"
#include "Command.h"
#include "CommandParser.h"
#include "Experiment/Experiment.h"

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
			return "./save/";
		}

		Experiment::Parameters& getExperimentParameters() { return mExperimentParameters; }
	private:
		std::unique_ptr<CommandParser> mParser;

		std::unique_ptr<Board> mBoard;

		Experiment::Parameters mExperimentParameters = {
			{35, 35}, // Board size
			100, // Initial population
			100, // Max generations
			500000, // Max attempts
			10, // Minimum lifetime
			6, // Threads
		};

		bool mQuitRequested = false;

		std::unique_ptr<Command> getCommand();
		void executeCommand(Command* command);

		std::unique_ptr<Command> parseInput();
	};
}
