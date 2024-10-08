#pragma once

#include <vector>

#include "Frame.h"

#include "../Array2D.h"

namespace GameOfLife::Experiment
{
	class Pattern
	{
	public:
		// TODO: Temporary constructor for testing
		Pattern();

		// Get whether the board contains this pattern at a specific
		// frame
		// If the frame number is higher than the number of frames,
		// it will loop back and move by mOffset
		bool boardContainsFrame(const Board& board, int frameNumber) const;
	private:
		std::vector<Frame> mFrames;
		// The total size of the pattern and all its frames
		Vec2 mSize;
	};
}