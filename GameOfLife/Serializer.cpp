#include "Serializer.h"

#include <sstream>

namespace GameOfLife {
	std::string Serializer::serialize(Board& board)
	{
		std::string result;
		result += std::to_string(Version) + '\n';

		result +=
			std::to_string(board.getSize().x)
			+ ' '
			+ std::to_string(board.getSize().y) + '\n';

		result += cellsToString(board.getCells());
		result += cellsToString(board.getInitialCells());

		return result;
	}

	// Read a line from a stringstream, advancing the stream
	std::string getLine(std::stringstream& stream)
	{
		std::string line;
		std::getline(stream, line);
		return line;
	}

	[[noreturn]] void fail(std::string_view message)
	{
		throw std::invalid_argument(std::string(message));
	}

	Array2D<CellState> readCells(std::stringstream& stream, Vec2 size)
	{
		Array2D<CellState> cells(size);

		for (int y = 0; y < size.y; y++)
		{
			auto line = getLine(stream);
			if (line.size() != size.x)
				fail("Invalid line length: " + line);

			for (int x = 0; x < size.x; x++)
			{
				CellState state;
				switch (line[x])
				{
				case DeadCellChar: state = CellState::Dead; break;
				case AliveCellChar: state = CellState::Alive; break;
				default: fail("Invalid cell character: " + line[x]);
				}

				cells[{x, y}] = state;
			}
		}

		return cells;
	}

	Board Serializer::deserialize(std::string_view str)
	{
		auto stream = std::stringstream(std::string(str));

		int version = std::stoi(getLine(stream));
		if (version != Version)
			fail("Invalid version, got " + std::to_string(version) + " expected " + std::to_string(Version));

		auto sizeLine = getLine(stream);
		auto space = sizeLine.find(' ');
		if (space == std::string::npos)
			fail("Invalid size line: " + sizeLine);

		int width = std::stoi(sizeLine.substr(0, space));
		int height = std::stoi(sizeLine.substr(space + 1));

		auto cells = readCells(stream, { width, height });
		auto initialCells = readCells(stream, { width, height });

		// Make sure we consumed everything
		if (stream.peek() != EOF)
			fail("Extra data in stream");

		return Board(cells, initialCells);
	}
}