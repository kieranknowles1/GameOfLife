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

		// Get all positions of this pattern in the board
		std::vector<Vec2> boardContainsStart(const Board& board) const;

		// Get whether the board contains this pattern at a specific
		// position and frame number
		// If the frame number is higher than the number of frames,
		// it will loop back and move by mOffset
		bool existsAtPosition(const Board& board, Vec2 position, int frameNumber) const;
	private:
		std::vector<Frame> mFrames;
		// The total size of the pattern and all its frames
		Vec2 mSize;
		// The offset of the pattern after each loop through all frames
		Vec2 mOffset;
	};
}