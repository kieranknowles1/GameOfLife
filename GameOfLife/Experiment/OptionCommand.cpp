#include "OptionCommand.h"

#include <iostream>

#include "../Controller.h"

namespace GameOfLife::Experiment
{
	OptionCommand::OptionCommand(std::string_view args)
	{
		if (args.empty()) return; // No arguments, show current values

		auto space = args.find(' ');
		if (space == std::string_view::npos)
			throw std::invalid_argument("Invalid number of arguments, expected 2");

		mKey = std::string(args.substr(0, space));
		mValue = std::string(args.substr(space + 1));
	}

	void OptionCommand::execute(Controller* context)
	{
		if (mKey.empty())
		{
			printOptions(context);
		}
		else
		{
			setOption(context, mKey, mValue);
		}
	}

	static void printOpt(std::string_view key, int value)
	{
		std::cout << key << ": " << value << std::endl;
	}

	void OptionCommand::printOptions(Controller* context)
	{
		auto& params = context->getExperimentParameters();
		printOpt("width", params.mBoardSize.x);
		printOpt("height", params.mBoardSize.y);
		printOpt("population", params.mInitialPopulation);
		printOpt("generations", params.mMaxGenerations);
		printOpt("attempts", params.mMaxAttempts);
		printOpt("lifetime", params.mMinimumLifetime);
		printOpt("threads", params.mThreads);
	}

	void OptionCommand::setOption(Controller* context, std::string_view key, std::string_view value)
	{
		auto& params = context->getExperimentParameters();
		// Every option is an integer, so parse it as such
		int intValue = std::stoi(std::string(value));

		if (key == "width")
			params.mBoardSize.x = intValue;
		else if (key == "height")
			params.mBoardSize.y = intValue;
		else if (key == "population")
			params.mInitialPopulation = intValue;
		else if (key == "generations")
			params.mMaxGenerations = intValue;
		else if (key == "attempts")
			params.mMaxAttempts = intValue;
		else if (key == "lifetime")
			params.mMinimumLifetime = intValue;
		else if (key == "threads")
			params.mThreads = intValue;
		else
			throw std::invalid_argument("Invalid option key");
	}
}