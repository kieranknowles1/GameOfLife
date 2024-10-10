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
			"test [pattern]\n"
			"  pattern: The name of the pattern to test\n"
			" The final state of the board will be stored, and can be manipulated with the usual commands\n";


		ExperimentCommand(std::string_view args);

		void execute(Controller* context) override;
	private:
		std::string mExperiment;

		void printFinalResult(Result* result);
	};
}