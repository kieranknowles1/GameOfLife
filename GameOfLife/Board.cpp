#include "Board.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <set>

namespace GameOfLife {
	void Board::fillRandom(int aliveCells, Random& rng)
	{
		auto size = mCells.getSize();
		if (aliveCells > (size.x * size.y))
		{
			throw std::invalid_argument("aliveCells cannot be greater than the number of cells");
		}

		std::uniform_int_distribution xDist(0, size.x - 1);
		std::uniform_int_distribution yDist(0, size.y - 1);

		int cellsLeft = aliveCells;
		while (cellsLeft > 0) {
			Vec2 pos = { xDist(rng), yDist(rng) };
			// Don't place more than one cell in the same position
			// The check above ensures that we don't get stuck in an infinite loop
			if (mCells[pos] == CellState::Dead)
			{
				mCells[pos] = CellState::Alive;
				--cellsLeft;
			}
		}

		mInitialCells = mCells;
	}

	Board::Board(Vec2 size)
		: mCells(size)
		, mInitialCells(size)
	{
	}

	void Board::iterate()
	{
		auto newCells = Array2D<CellState>(mCells.getSize());

		for (int x = 0; x < mCells.getSize().x; ++x)
		{
			for (int y = 0; y < mCells.getSize().y; ++y)
			{
				Vec2 pos = { x, y };
				int aliveNeighbours = getAliveNeighbours(pos);

				newCells[pos] = getNewState(aliveNeighbours, mCells[pos]);
			}
		}

		mCells = newCells;
	}

	CellState Board::getNewState(int aliveNeighbours, CellState state)
	{
		switch (state)
		{
		case CellState::Alive:
			if (aliveNeighbours < 2)
				return CellState::Dead; // Underpopulation
			if (aliveNeighbours > 3)
				return CellState::Dead; // Overpopulation
			return CellState::Alive; // Lives on
		case CellState::Dead:
			return aliveNeighbours == 3 ? CellState::Alive : CellState::Dead;
		default:
			__assume(false && "Invalid CellState"); // Suppress warning about lack of return
		}
	}

	int Board::getAliveNeighbours(Vec2 pos)
	{
		int alive = 0;
		for (int x = pos.x - 1; x <= pos.x + 1; x++)
		{
			for (int y = pos.y - 1; y <= pos.y + 1; y++)
			{
				auto neighbour = Vec2(x, y);
				if (neighbour == pos || !mCells.isValid(neighbour))
					continue;

				if (mCells[neighbour] == CellState::Alive)
					alive++;
			}
		}
		return alive;
	}

	std::string Board::toString()
	{
		return mCells.serializeBody();
	}
}