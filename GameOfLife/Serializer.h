#pragma once

#include <string>

#include "Board.h"
#include "Experiment/Pattern.h"

namespace GameOfLife {
	class Serializer
	{
	public:
		// Version of serialize format. Increment when
		// making a breaking change
		static constexpr int Version = 3;

		Serializer() = delete; // This is a static class

		// Serialize the board to a string so it can be loaded later
		static std::string serialize(Board& board);
		// Load a board from a string
		static Board deserializeBoard(std::string_view str);

		static Experiment::Pattern deserializePattern(std::string_view str);
	private:

	};
}