#include "CommandParser.h"

#include <cassert>

#include "HelpCommand.h"
#include "ShowCommand.h"
#include "InitCommand.h"
#include "IterateCommand.h"
#include "SaveCommand.h"
#include "LoadCommand.h"
#include "QuitCommand.h"
#include "Experiment/ExperimentCommand.h"
#include "Experiment/EfficiencyCommand.h"

namespace GameOfLife {
	void registerDefaultCommands(CommandParser* parser)
	{
		// Register the default set of commands
		// Templates allow the compiler to generate a factory for each command
		parser->registerFactory(new CommandFactoryImpl<HelpCommand>());
		parser->registerFactory(new CommandFactoryImpl<ShowCommand>());
		parser->registerFactory(new CommandFactoryImpl<InitCommand>());
		parser->registerFactory(new CommandFactoryImpl<IterateCommand>());
		parser->registerFactory(new CommandFactoryImpl<SaveCommand>());
		parser->registerFactory(new CommandFactoryImpl<LoadCommand>());
		parser->registerFactory(new CommandFactoryImpl<QuitCommand>());
		parser->registerFactory(new CommandFactoryImpl<Experiment::ExperimentCommand>());
		parser->registerFactory(new CommandFactoryImpl<Experiment::EfficiencyCommand>());
	}

	CommandParser::~CommandParser()
	{
		for (auto& factory : mFactories)
		{
			delete factory.second;
		}
	}

	std::unique_ptr<Command> CommandParser::parseInput(std::string_view input)
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
