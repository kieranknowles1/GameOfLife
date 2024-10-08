#include "Serializer.h"

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
}