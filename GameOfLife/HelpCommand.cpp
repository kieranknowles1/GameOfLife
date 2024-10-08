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
		{
			std::cout << "Available commands:" << std::endl;
			for (const auto& factory : parser->getFactories())
			{
				std::cout << "  " << factory.first << " - " << factory.second->getSummary() << std::endl;
			}
		}
		else
		{
			std::cout << parser->getFactory(mCommand)->getUsage() << std::endl;
		}
	}
}