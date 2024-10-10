#include "Experiment.h"

#include <iostream>

#include "ExperimentRunner.h"

namespace GameOfLife::Experiment {
	Result Experiment::run()
	{
		for (int attempt = 0; attempt < mParameters.mMaxAttempts; attempt++)
		{
			mTasks.emplace_back(*this, attempt);
		}
		return dispatch();
	}

	Result Experiment::dispatch()
	{
		// TODO: Use multiple threads
		while (!mTasks.empty())
		{
			auto task = std::move(mTasks.back());
			mTasks.pop_back();

			auto result = task.run();
			if (result.mSuccess)
				return result;
		}

		return Result::Failure();
	}
}