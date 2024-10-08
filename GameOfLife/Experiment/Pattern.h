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
	private:
		std::vector<Frame> mFrames;
		// The total size of the pattern and all its frames
		Vec2 mSize;
		// The offset of the pattern after each loop through all frames
		Vec2 mOffset;
	};
}