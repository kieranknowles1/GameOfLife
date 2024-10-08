#include "Pattern.h"

namespace GameOfLife::Experiment
{
	Pattern::Pattern()
		: mSize({ 4, 4 })
	{
		auto cells = Array2D<CellState>(mSize);
		cells[{1, 1}] = CellState::Alive;
		cells[{2, 1}] = CellState::Alive;
		cells[{1, 2}] = CellState::Alive;
		cells[{2, 2}] = CellState::Alive;
		mFrames.push_back(Frame(cells));
	}
	bool Pattern::boardContainsFrame(const Board& board, int frameNumber) const
	{
		int frameIndex = frameNumber % mFrames.size();

		auto& frame = mFrames[frameIndex];
		
		return frame.boardContains(board);
	}
}