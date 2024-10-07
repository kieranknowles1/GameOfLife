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

	class Board
	{
	public:
		static constexpr char DeadCellChar = '.';
		static constexpr char AliveCellChar = 'O';

		void fillRandom(int aliveCells, Random& rng);

		Board(Vec2 size);

		// Run one iteration of the game of life
		void iterate();

		std::string toString();
	private:
		Array2D<CellState> mCells;

		CellState getNewState(int aliveNeighbours, CellState state);

		// Get the number of alive neighbours of a cell
		int getAliveNeighbours(Vec2 pos);
	};
}