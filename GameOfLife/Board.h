#pragma once

#include <string>
#include <random>

#include "Array2D.h"

namespace GameOfLife {
	using Random = std::mt19937;

	enum class CellState : bool
	{
		Dead = false,
		Alive = true
	};

	static constexpr char DeadCellChar = '.';
	static constexpr char AliveCellChar = 'O';

	std::string cellsToString(const Array2D<CellState>& cells);

	class Board
	{
	public:
		void fillRandom(int aliveCells, Random& rng);

		Board(Vec2 size);
		Board(Array2D<CellState> cells, Array2D<CellState> initialCells)
			: mCells(std::move(cells))
			, mInitialCells(std::move(initialCells))
		{
		}

		// Run one iteration of the game of life
		void iterate();

		std::string toString();

		Vec2 getSize() const { return mCells.getSize(); }

		Array2D<CellState>& getCells() { return mCells; }
		Array2D<CellState>& getInitialCells() { return mInitialCells; }
	private:
		Array2D<CellState> mInitialCells;
		Array2D<CellState> mCells;

		CellState getNewState(int aliveNeighbours, CellState state);

		// Get the number of alive neighbours of a cell
		int getAliveNeighbours(Vec2 pos);
	};
}