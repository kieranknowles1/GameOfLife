#pragma once

#include <string>
#include <fstream>
#include <filesystem>

namespace GameOfLife {
	class Board;
	struct Vec2;
	namespace Experiment {
		class Pattern;
	}

	class Serializer
	{
	private:
		Serializer() = delete; // This is a static class
	public:
		// Version of serialize format. Increment when
		// making a breaking change
		static constexpr int Version = 3;

		// Read a file in its entirety to a string
		static std::string readFile(const std::filesystem::path& path);
		static std::ofstream openWrite(const std::filesystem::path& path);

		static std::string getLine(std::stringstream& stream);
		static void checkVersion(std::stringstream& stream);

		// Serialize the board to a string so it can be loaded later
		static std::string serialize(Board& board);
		// Load a board from a string
		static Board deserializeBoard(std::string_view str);

		static Experiment::Pattern deserializePattern(std::string_view str);

		static Vec2 readVec2(std::stringstream& stream);
	private:

	};
}