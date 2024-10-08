#include "Board.h"

#include <cassert>
#include <iostream>
#include <sstream>
#include <set>

namespace GameOfLife {
	// Format:
	// <width> <height>
	// <data>
	std::string cellsToString(const Array2D<CellState>& cells)
	{
		std::stringstream ss;

		for (int y = 0; y < cells.getSize().y; ++y)
		{
			for (int x = 0; x < cells.getSize().x; ++x)
			{
				char repr = cells[{x, y}] == CellState::Alive ? AliveCellChar : DeadCellChar;
				ss << repr;
			}
			ss << '\n';
		}

		return ss.str();
	}

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
		auto neighbours = {
			Vec2(pos.x - 1, pos.y - 1), // top left
			Vec2(pos.x, pos.y - 1), // top
			Vec2(pos.x + 1, pos.y - 1), // top right
			Vec2(pos.x - 1, pos.y), // left
			Vec2(pos.x + 1, pos.y), // right
			Vec2(pos.x - 1, pos.y + 1), // bottom left
			Vec2(pos.x, pos.y + 1), // bottom
			Vec2(pos.x + 1, pos.y + 1) // bottom right
		};

		int aliveNeighbours = 0;
		for (auto neighbour : neighbours)
		{
			if (mCells.isValid(neighbour) && mCells[neighbour] == CellState::Alive)
			{
				++aliveNeighbours;
			}
		}
		return aliveNeighbours;
	}

	std::string Board::toString()
	{
		return cellsToString(mCells);
	}
}