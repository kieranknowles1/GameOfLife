#pragma once

#include <memory>

#include "Command.h"
#include "CommandParser.h"

namespace GameOfLife
{
	class Controller
	{
	public:
		Controller(CommandParser& parser) :
			mParser(parser),
			mQuitRequested(false)
		{}

		// Run the controller until the user quits
		void run();

		// Request the controller to quit at the next opportunity
		void requestQuit() { mQuitRequested = true; }
	private:
		CommandParser mParser;
		bool mQuitRequested = false;
		// TODO: Use smart pointers everywhere
		Command* parseInput();
	};
}
