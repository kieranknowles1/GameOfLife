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
			"test [pattern] [width] [height] [population] [generations] [attempts] [lifetime]\n"
			"  pattern: The name of the pattern to test\n"
			"  width: The width of the board (optional)\n"
			"  height: The height of the board (optional)\n"
			"  population: The number of cells to start with (optional)\n"
			"  generations: The number of generations to run each attempt (optional)\n"
			"  lifetime: The minimum lifetime of the pattern to consider the experiment a success (optional)\n"
			" The final state of the board will be stored, and can be manipulated with the usual commands\n";


		ExperimentCommand(std::string_view args);

		void execute(Controller* context) override;
	private:
		std::string mExperiment;
		Parameters mParameters;

		void printFinalResult(Result& result);
	};
}