#include "Serializer.h"

#include <sstream>

namespace GameOfLife {
	std::string getLine(std::stringstream& stream)
	{
		std::string line;
		std::getline(stream, line);
		return line;
	}

	// Check that the version number matches what we expect
	void checkVersion(std::stringstream& stream)
	{
		int version = std::stoi(getLine(stream));
		if (version != Serializer::Version)
			throw std::runtime_error("Invalid version, got " + std::to_string(version) + " expected " + std::to_string(Serializer::Version));
	}

	std::string Serializer::serialize(Board& board)
	{
		std::string result;
		result += std::to_string(Version) + '\n';

		result += board.getCells().serialize();
		result += board.getInitialCells().serialize();

		return result;
	}

	Board Serializer::deserializeBoard(std::string_view str)
	{
		auto stream = std::stringstream(std::string(str));
		checkVersion(stream);

		auto state = Array2D<CellState>::deserialize(stream);
		auto initialState = Array2D<CellState>::deserialize(stream);

		return Board(state, initialState);
	}

	// Format:
	// FrameCount: Int
	// Offset: Vec2
	// Frames[FrameCount]
	Experiment::Pattern Serializer::deserializePattern(std::string_view str)
	{
		auto stream = std::stringstream(std::string(str));
		checkVersion(stream);

		int frameCount = std::stoi(getLine(stream));

		std::vector<Experiment::Frame> frames;

		// TODO: ReadVector function
		auto offsetLine = getLine(stream);
		auto space = offsetLine.find(' ');
		int x = std::stoi(offsetLine.substr(0, space));
		int y = std::stoi(offsetLine.substr(space + 1));
		Vec2 offset{ x, y };

		for (int i = 0; i < frameCount; i++) {
			auto cells = Array2D<CellState>::deserialize(stream);
			frames.emplace_back(cells);
		}

		return Experiment::Pattern(frames, frames[0].getSize(), offset);
	}
}