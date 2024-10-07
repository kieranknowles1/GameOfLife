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

		static constexpr int SerializeVersion = 1;

		void fillRandom(int aliveCells, Random& rng);

		Board(Vec2 size);

		// Run one iteration of the game of life
		void iterate();

		std::string toString();

		// Serialize the board to a string so it can be loaded later
		std::string serialize();

		// Load a board from a string
		static Board deserialize(std::string_view str);
	private:
		Array2D<CellState> mInitialCells;
		Array2D<CellState> mCells;

		std::string cellsToString(const Array2D<CellState>& cells);

		CellState getNewState(int aliveNeighbours, CellState state);

		// Get the number of alive neighbours of a cell
		int getAliveNeighbours(Vec2 pos);
	};
}