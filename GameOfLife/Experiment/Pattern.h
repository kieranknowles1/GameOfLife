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

		Pattern(std::vector<Frame> frames, Vec2 size, Vec2 offset)
			: mFrames(std::move(frames))
			, mSize(size)
			, mOffset(offset)
		{}

		// Get the current position of the pattern at a specific frame number
		Vec2 getCurrentPosition(Vec2 startingPosition, int frameNumber) const;

		// Get all positions of the pattern's first frame in the board
		std::vector<Vec2> findInstances(const Board& board) const;

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