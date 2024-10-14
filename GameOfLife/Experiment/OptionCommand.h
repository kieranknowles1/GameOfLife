#pragma once

#include "../Command.h"

#include "Experiment.h"

namespace GameOfLife::Experiment
{
	class OptionCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "option";
		static constexpr std::string_view Summary = "Set the options for experiments";
		static constexpr std::string_view Usage =
			"option [key] [value]\n"
			"  key: The option to set\n"
			"  value: The value to set the option to\n"
			"  If key is not provided, all options are printed\n";


		OptionCommand(std::string_view args);

		void execute(Controller* context) override;
	private:
		std::string mKey;
		std::string mValue;

		void printOptions(Controller* context);
		void setOption(Controller* context, std::string_view key, std::string_view value);
	};
}