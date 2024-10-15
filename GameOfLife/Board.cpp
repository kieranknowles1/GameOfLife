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

		// Fill the requested number of cells randomly
		for (int i = 0; i < aliveCells; i++)
			placeRandom(rng);

		mInitialCells = mCells;
	}

	void Board::placeRandom(Random& rng)
	{
		// -1 for the edge cells
		std::uniform_int_distribution xDist(0, mCells.getSize().x - 1);
		std::uniform_int_distribution yDist(0, mCells.getSize().y - 1);

		while (true) {
			Vec2 pos = { xDist(rng), yDist(rng) };
			if (mCells[pos] == CellState::Dead)
			{
				mCells[pos] = CellState::Alive;
				return;
			}
		}
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

	void Board::iterate(int iterations, bool print)
	{
		for (int i = 0; i < iterations; i++)
		{
			iterate();
			if (print)
			{
				std::cout << toString() << std::endl;
			}
		}
	}

	CellState Board::getNewState(int aliveNeighbours, CellState state)
	{
		if (state == CellState::Dead)
			return aliveNeighbours == 3 ? CellState::Alive : CellState::Dead; // Birth
		else // alive
			// Under/overpopulation
			return aliveNeighbours == 2 || aliveNeighbours == 3 ? CellState::Alive : CellState::Dead;
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

	std::string Board::getCornerDots()
	{
		std::string result;
		for (int x = 0; x < mCells.getSize().x; x++)
		{
			result += ". ";
		}
		result += "."; // Add the last corner
		return result;
	}

	std::string Board::toString()
	{
		// Alternate between dots for corners, and spaces/O for cells
		std::string corners = getCornerDots();
		std::string result;

		for (int y = 0; y < mCells.getSize().y; y++)
		{
			result += corners + "\n";
			for (int x = 0; x < mCells.getSize().x; x++)
			{
				result += mCells[Vec2(x, y)] == CellState::Alive ? " O" : "  ";
			}
			result += "\n";
		}
		return result + corners;
	}
}