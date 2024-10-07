#pragma once

#include <string>
#include <random>

#include "Array2D.h"

namespace GameOfLife {
	using Random = std::mt19937;

	enum class Cell : bool
	{
		Dead = false,
		Alive = true
	};

	class Board
	{
	public:
		static constexpr char DeadCellChar = '.';
		static constexpr char AliveCellChar = 'O';

		// TODO: Implement this function
		static Board createRandom(Vec2 size, int aliveCells, Random& rng);

		Board(Vec2 size);

		std::string toString();
	private:
		Array2D<Cell> mCells;
	};
}