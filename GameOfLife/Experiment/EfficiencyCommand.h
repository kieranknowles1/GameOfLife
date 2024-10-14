#pragma once

#include "../Command.h"

#include "Experiment.h"

namespace GameOfLife::Experiment
{
	struct EfficiencyResult
	{
		Parameters params;
		std::unique_ptr<Result> result;
	};

	class EfficiencyCommand : public Command
	{
	public:
		// A cell needs 3 neighbours to be born and 2 to survive, so anything with less than 3 cells
		// will die immediately
		static constexpr int MinPossibleCells = 3;

		static constexpr std::string_view Identifier = "ern";
		static constexpr std::string_view Summary = "Get the efficiency resource number of a pattern";
		static constexpr std::string_view Usage =
			"ern [pattern]\n"
			"  pattern: The name of the pattern to find\n"
			" The final state of the board will be stored, and can be manipulated with the usual commands\n";


		EfficiencyCommand(std::string_view args);

		void execute(Controller* context) override;
	private:
		std::string mExperiment;

		EfficiencyResult runTests(Pattern& pattern, int bruteForceErn);

		std::unique_ptr<Result> attemptExperiment(std::vector<Pattern>& patterns, Parameters& params);

		void printFinalResult(EfficiencyResult* result, Pattern* pattern);
	};
}