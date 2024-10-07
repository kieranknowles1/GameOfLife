#include "Board.h"

#include <set>

namespace GameOfLife {
	Board Board::createRandom(Vec2 size, int aliveCells, Random& rng)
	{
		if (aliveCells > (size.x * size.y))
		{
			throw std::invalid_argument("aliveCells cannot be greater than the number of cells");
		}

		Board board(size);

		std::uniform_int_distribution xDist(0, size.x - 1);
		std::uniform_int_distribution yDist(0, size.y - 1);

		int cellsLeft = aliveCells;
		while (cellsLeft > 0) {
			Vec2 pos = { xDist(rng), yDist(rng) };
			// Don't place more than one cell in the same position
			// The check above ensures that we don't get stuck in an infinite loop
			if (board.mCells[pos] == Cell::Dead)
			{
				board.mCells[pos] = Cell::Alive;
				--cellsLeft;
			}
		}

		return board;
	}

	Board::Board(Vec2 size)
		: mCells(size)
	{
	}

	std::string Board::toString()
	{
		std::string result;

		for (int y = 0; y < mCells.getSize().y; ++y)
		{
			for (int x = 0; x < mCells.getSize().x; ++x)
			{
				result += mCells[{x, y}] == Cell::Alive ? AliveCellChar : DeadCellChar;
			}
			result += '\n';
		}

		return result;
	}
}