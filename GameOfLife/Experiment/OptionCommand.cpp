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
	void OptionCommand::printOptions(Controller* context)
	{
		for (auto& [name, value] : context->getExperimentParameters().getValuesMap())
		{
			std::cout << name << ": " << *value << std::endl;
		}
	}

	int* OptionCommand::getValueRef(Parameters& params, std::string_view key)
	{
		auto values = params.getValuesMap();
		auto ref = values.find(key);
		if (ref == values.end())
			throw std::invalid_argument("Invalid key");
		return ref->second;
	}

	void OptionCommand::setOption(Controller* context, std::string_view key, std::string_view value)
	{
		auto& params = context->getExperimentParameters();
		int* ref = getValueRef(params, key);
		*ref = std::stoi(std::string(value));
	}
}