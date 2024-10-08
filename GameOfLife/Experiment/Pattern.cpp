#include "Pattern.h"

namespace GameOfLife::Experiment
{
	Pattern::Pattern()
		: mSize({ 2, 2 })
		, mOffset({ 0, 0 })
	{
		// Temporary: Create a box pattern
		auto cells = Array2D<CellState>({ 2, 2 });
		cells[{0, 0}] = CellState::Alive;
		cells[{0, 1}] = CellState::Alive;
		cells[{1, 0}] = CellState::Alive;
		cells[{1, 1}] = CellState::Alive;

		mFrames.push_back(Frame(cells));
	}
}