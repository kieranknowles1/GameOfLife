#pragma once

#include <string>
#include <random>

#include "Array2D.h"
#include "Cell.h"

namespace GameOfLife {
	using Random = std::mt19937;

	class Board
	{
	public:
		void fillRandom(int aliveCells, Random& rng);
		// Randomly place a cell in an empty position
		void placeRandom(Random& rng);

		Board(Vec2 size);
		Board(Array2D<CellState> cells, Array2D<CellState> initialCells)
			: mCells(std::move(cells))
			, mInitialCells(std::move(initialCells))
		{
		}
		Board(Array2D<CellState> initialCells)
			: mCells(initialCells)
			, mInitialCells(initialCells)
		{
		}

		// Run one iteration of the game of life
		void iterate();
		// Run a number of iterations of the game of life, optionally printing the board at each step
		void iterate(int generations, bool print = false);

		std::string toString();

		Vec2 getSize() const { return mCells.getSize(); }

		Array2D<CellState>& getCells() { return mCells; }
		const Array2D<CellState>& getCells() const { return mCells; }
		Array2D<CellState>& getInitialCells() { return mInitialCells; }
	private:
		Array2D<CellState> mInitialCells;
		Array2D<CellState> mCells;

		std::string getCornerDots();

		CellState getNewState(int aliveNeighbours, CellState state);

		// Get whether a cell is alive. Out of bounds cells are considered dead
		bool isAlive(Vec2 pos);
		// Get the number of alive neighbours of a cell
		int getAliveNeighbours(Vec2 pos);
	};
}
