#pragma once

#include <string>

namespace GameOfLife {
	class Board;
	struct Vec2;
	namespace Experiment {
		class Pattern;
	}

	class Serializer
	{
	public:
		// Version of serialize format. Increment when
		// making a breaking change
		static constexpr int Version = 3;

		Serializer() = delete; // This is a static class

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