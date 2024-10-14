#include "Pattern.h"

namespace GameOfLife::Experiment
{
	Vec2 Pattern::getCurrentPosition(Vec2 startingPosition, int frameNumber) const
	{
		int frameIndex = frameNumber % mFrames.size();
		int iterations = frameNumber / mFrames.size();
		Vec2 offset = mOffset * iterations;

		return startingPosition + offset;
	}

	std::vector<Vec2> Pattern::findInstances(const Board& board) const
	{
		auto& frame = mFrames[0];
		
		return frame.findInstances(board);
	}

	bool Pattern::existsAtPosition(const Board& board, Vec2 position, int frameNumber) const
	{
		Vec2 currentPosition = getCurrentPosition(position, frameNumber);

		int frameIndex = frameNumber % mFrames.size();

		auto& frame = mFrames[frameIndex];
		// TODO: Does this handle gliders properly?

		return frame.pointContains(getCurrentPosition(position, frameNumber), board);
	}

	int Pattern::getCellCount() const
	{
		int lowest = std::numeric_limits<int>::max();
		for (auto& frame : mFrames)
		{
			int count = frame.getCellCount();
			if (count < lowest)
				lowest = count;
		}

		return lowest;
	}
}