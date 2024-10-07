#pragma once

#include <map>

#include "Command.h"

namespace GameOfLife
{
	class CommandParser;

	// Register the default set of commands
	void registerDefaultCommands(CommandParser& parser);

	class CommandParser
	{
	public:
		Command* parseInput(std::string_view input);

		void registerFactory(CommandFactory* factory);
	private:
		std::map<std::string, CommandFactory*> mFactories;
	};
}