#include "Controller.h"

namespace GameOfLife
{
	void Controller::run()
	{
		while (!mQuitRequested)
		{
			auto input = parseInput();
			input->execute(this);
		}
	}

	Command* Controller::parseInput()
	{
		// TODO: Read input from the user
		return mParser.parseInput("help");
	}
}