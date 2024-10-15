#include "Serializer.h"

#include <sstream>

#include "Array2D.h"
#include "Board.h"
#include "Experiment/Pattern.h"

namespace GameOfLife {
	std::string Serializer::readFile(const std::filesystem::path& path)
	{
		std::ifstream file(path);
		if (!file.good())
			throw std::runtime_error("Failed to open file for reading: " + path.string());
		
		return std::string(std::istreambuf_iterator<char>(file), {});
	}

	std::ofstream Serializer::openWrite(const std::filesystem::path& path)
	{
		std::ofstream file(path);
		if (!file.good())
			throw std::runtime_error("Failed to open file for writing: " + path.string());
		return std::move(file);
	}

	std::string Serializer::getLine(std::stringstream& stream)
	{
		std::string line;
		std::getline(stream, line);
		return line;
	}

	// Check that the version number matches what we expect
	void Serializer::checkVersion(std::stringstream& stream)
	{
		int version = std::stoi(getLine(stream));
		if (version != Version)
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

		auto offset = readVec2(stream);

		for (int i = 0; i < frameCount; i++) {
			auto cells = Array2D<CellState>::deserialize(stream);
			frames.emplace_back(cells);
		}

		return Experiment::Pattern(frames, frames[0].getSize(), offset);
	}

	Vec2 Serializer::readVec2(std::stringstream& stream)
	{
		auto line = getLine(stream);
		auto space = line.find(' ');
		int x = std::stoi(line.substr(0, space));
		int y = std::stoi(line.substr(space + 1));
		return Vec2{ x, y };
	}
}