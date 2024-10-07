#include "CommandParser.h"

#include <cassert>

#include "HelpCommand.h"

namespace GameOfLife {
	void registerDefaultCommands(CommandParser& parser)
	{
		parser.registerFactory(new TypedCommandFactory<HelpCommand>());
	}

	Command* CommandParser::parseInput(std::string_view input)
	{
		return mFactories.find(input.data())->second->create(input);
	}

	void CommandParser::registerFactory(CommandFactory* factory)
	{
		auto name = std::string(factory->getIdentifier());

		assert(mFactories.find(name) == mFactories.end() && "Identifiers must be unique");

		mFactories[name] = factory;
	}
}