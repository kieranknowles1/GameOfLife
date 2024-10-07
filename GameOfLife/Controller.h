#pragma once

#include <memory>

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
	private:
		std::unique_ptr<CommandParser> mParser;
		bool mQuitRequested = false;
		// TODO: Use smart pointers everywhere
		std::unique_ptr<Command> parseInput();
	};
}
