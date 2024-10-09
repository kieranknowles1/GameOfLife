#pragma once

#include <string>

#include "Board.h"

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
		static Board deserialize(std::string_view str);

	private:

	};
}