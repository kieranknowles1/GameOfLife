#include "Pattern.h"

namespace GameOfLife::Experiment
{
	Pattern::Pattern()
		: mSize({ 4, 4 })
		, mOffset({ 0, 0 })
	{
		auto cells = Array2D<CellState>(mSize);
		cells[{1, 1}] = CellState::Alive;
		cells[{2, 1}] = CellState::Alive;
		cells[{1, 2}] = CellState::Alive;
		cells[{2, 2}] = CellState::Alive;
		mFrames.push_back(Frame(cells));
	}
	std::vector<Vec2> Pattern::findInstances(const Board& board) const
	{
		auto& frame = mFrames[0];
		
		return frame.findInstances(board);
	}

	bool Pattern::existsAtPosition(const Board& board, Vec2 position, int frameNumber) const
	{
		int frameIndex = frameNumber % mFrames.size();
		int iterations = frameNumber / mFrames.size();
		Vec2 offset = mOffset * iterations;

		auto& frame = mFrames[frameIndex];
		// TODO: Does this handle gliders properly?

		return frame.pointContains(position - offset, board);
	}
}