#pragma once

#include <string>

#include "Array2D.h"

namespace GameOfLife
{
	enum class CellState : char
	{
		Dead,
		Alive
	};
	static constexpr char DeadCellChar = '.';
	static constexpr char AliveCellChar = 'O';

	static CellState cellFromChar(char c) {
		switch (c)
		{
		case DeadCellChar: return CellState::Dead;
		case AliveCellChar: return CellState::Alive;
		default: throw std::runtime_error("Invalid cell character: " + c);
		}
	}

	// Specialisation of Array2D::serializeBody for CellState
	// Defined in CPP to avoid multiple definition link error
	template <>
	std::string Array2D<CellState>::serializeBody() const;

	template <>
	void Array2D<CellState>::deserializeBody(std::stringstream& str);
}
