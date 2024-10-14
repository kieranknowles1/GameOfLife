#include "Frame.h"

namespace GameOfLife::Experiment
{
	std::vector<Vec2> Frame::findInstances(const Board& board) const
	{
		// We search from the top left, so skip
		// places where the frame would be out of bounds
		int maxX = board.getSize().x - mCells.getSize().x;
		int maxY = board.getSize().y - mCells.getSize().y;

		std::vector<Vec2> positions;

		for (int x = 0; x <= maxX; x++)
		{
			for (int y = 0; y <= maxY; y++)
			{
				if (pointContains({ x, y }, board))
					positions.push_back({ x, y });
			}
		}
		return positions;
	}

	// Returns the state of the cell at pos, or Dead if out of bounds
	CellState getDefaultDead(Vec2 pos, const Board& board)
	{
		if (pos.x < 0 || pos.y < 0)
			return CellState::Dead;
		if (pos.x >= board.getSize().x || pos.y >= board.getSize().y)
			return CellState::Dead;
		return board.getCells()[pos];
	}

	bool Frame::pointContains(Vec2 topLeft, const Board& board) const
	{
		for (int x = 0; x < mCells.getSize().x; x++)
		{
			for (int y = 0; y < mCells.getSize().y; y++)
			{
				Vec2 pos = Vec2{ x, y } + topLeft;
				auto state = getDefaultDead(pos, board);
				auto expected = mCells[{x, y}];

				if (state != expected)
					return false;
			}
		}

		return true;
	}

	int Frame::getCellCount() const
	{
		int count = 0;
		for (int x = 0; x < mCells.getSize().x; x++)
		{
			for (int y = 0; y < mCells.getSize().y; y++)
			{
				if (mCells[{x, y}] == CellState::Alive)
					count++;
			}
		}
		return count;
	}
}
