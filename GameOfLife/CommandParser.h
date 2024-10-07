#pragma once

#include <map>
#include <stdexcept>

#include "Command.h"

namespace GameOfLife
{
	class InvalidCommandException : public std::invalid_argument
	{
	public:
		InvalidCommandException(std::string_view command) :
			std::invalid_argument("Invalid command: " + std::string(command))
		{}
	};



	class CommandParser;

	// Register the default set of commands
	void registerDefaultCommands(CommandParser* parser);

	class CommandParser
	{
	public:
		CommandParser() = default;
		// Disallow copying
		CommandParser(const CommandParser&) = delete;

		~CommandParser();

		using Factories = std::map<std::string, CommandFactory*>;

		std::unique_ptr<Command> parseInput(std::string_view input);

		void registerFactory(CommandFactory* factory);
		const Factories& getFactories() const { return mFactories; }

		// Get the factory for a specific command, or throw if it doesn't exist
		CommandFactory* getFactory(std::string_view identifier);
	private:
		Factories mFactories;
	};
}