#pragma once

#include "../Array2D.h"
#include "../Board.h"
#include "../Cell.h"

namespace GameOfLife::Experiment
{
	// A frame of a pattern, which is a 2D array of cells
	// should be padded with a row/column of dead cells
	// Out of bounds cells are considered dead
	class Frame
	{
	public:
		Frame(Array2D<CellState> cells)
			: mCells(cells)
		{
		}

		bool boardContains(const Board& board) const;

	private:
		bool pointContains(const Vec2 topLeft, const Board& board) const;

		Array2D<CellState> mCells;
	};
}