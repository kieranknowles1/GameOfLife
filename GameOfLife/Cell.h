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

	// Specialisation of Array2D::serializeBody for CellState
	// Defined in CPP to avoid multiple definition link error
	template <>
	std::string Array2D<CellState>::serializeBody() const;

	template <>
	void Array2D<CellState>::deserializeBody(std::stringstream& str);
}