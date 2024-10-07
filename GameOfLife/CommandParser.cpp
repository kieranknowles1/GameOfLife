#include "CommandParser.h"

#include <cassert>

#include "HelpCommand.h"
#include "QuitCommand.h"

namespace GameOfLife {
	void registerDefaultCommands(CommandParser& parser)
	{
		parser.registerFactory(new CommandFactoryImpl<HelpCommand>());
		parser.registerFactory(new CommandFactoryImpl<QuitCommand>());
	}

	Command* CommandParser::parseInput(std::string_view input)
	{
		auto space = input.find(' ');
		if (space == std::string_view::npos) space = input.size();

		auto command = input.substr(0, space);
		auto arguments = space < input.size() ? input.substr(space + 1) : "";

		return getFactory(command)->create(arguments);
	}

	void CommandParser::registerFactory(CommandFactory* factory)
	{
		auto name = std::string(factory->getIdentifier());

		assert(mFactories.find(name) == mFactories.end() && "Identifiers must be unique");

		mFactories[name] = factory;
	}

	CommandFactory* CommandParser::getFactory(std::string_view identifier)
	{
		auto factory = mFactories.find(std::string(identifier));
		if (factory == mFactories.end())
		{
			throw InvalidCommandException(identifier);
		}

		return factory->second;
	}
}