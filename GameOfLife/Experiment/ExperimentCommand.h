#pragma once

#include "../Command.h"

#include "Experiment.h"

namespace GameOfLife::Experiment
{
	class ExperimentCommand : public Command
	{
	public:
		static constexpr std::string_view Identifier = "test";
		static constexpr std::string_view Summary = "Run an experiment";
		static constexpr std::string_view Usage =
			"test [patterns...]\n"
			"  patterns: The name of the patterns to find\n"
			" The final state of the board will be stored, and can be manipulated with the usual commands\n";


		ExperimentCommand(std::string_view args);

		void execute(Controller* context) override;
	private:
		std::vector<std::string> mExperiment;

		void printFinalResult(Experiment* experiment, Result* result);
	};
}