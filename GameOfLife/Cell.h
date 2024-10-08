#pragma once

namespace GameOfLife
{
	enum class CellState : char
	{
		Dead,
		Alive
	};
	static constexpr char DeadCellChar = '.';
	static constexpr char AliveCellChar = 'O';
}