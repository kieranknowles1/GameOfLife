#include "Serializer.h"

#include <sstream>

namespace GameOfLife {
	std::string Serializer::serialize(Board& board)
	{
		std::string result;
		result += std::to_string(Version) + '\n';

		result += board.getCells().serialize();
		result += board.getInitialCells().serialize();

		return result;
	}

	Board Serializer::deserialize(std::string_view str)
	{
		auto stream = std::stringstream(std::string(str));

		std::string versionLine;
		std::getline(stream, versionLine);
		int version = std::stoi(versionLine);
		if (version != Version)
			throw std::runtime_error("Invalid version, got " + std::to_string(version) + " expected " + std::to_string(Version));

		auto state = Array2D<CellState>::deserialize(stream);
		auto initialState = Array2D<CellState>::deserialize(stream);

		return Board(state, initialState);
	}

	[[noreturn]] void fail(std::string_view message)
	{
		throw std::invalid_argument(std::string(message));
	}
}