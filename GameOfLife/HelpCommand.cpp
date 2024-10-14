#include "HelpCommand.h"

#include <iostream>

#include "Controller.h"

namespace GameOfLife {
	HelpCommand::HelpCommand(std::string_view input) :
		mCommand(input)
	{}

	void HelpCommand::execute(Controller* context)
	{
		auto parser = context->getParser();

		if (mCommand.empty())
			listAll(parser);
		else
			showHelp(parser, mCommand);
	}
	void HelpCommand::listAll(CommandParser* parser)
	{
		std::cout << "Available commands:" << std::endl;
		for (const auto& factory : parser->getFactories())
		{
			std::cout << "  " << factory.first << " - " << factory.second->getSummary() << std::endl;
		}
	}
	void HelpCommand::showHelp(CommandParser* parser, std::string_view command)
	{
		std::cout << parser->getFactory(command)->getUsage() << std::endl;
	}
}