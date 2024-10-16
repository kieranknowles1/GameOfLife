#include "Cell.h"

#include "Serializer.h"

namespace GameOfLife {
	std::string Array2D<CellState>::serializeBody() const {
		std::string result;

		for (int y = 0; y < mSize.y; y++) {
			for (int x = 0; x < mSize.x; x++) {
				auto state = this->operator[]({ x, y });
				result += state == CellState::Alive ? AliveCellChar : DeadCellChar;
			}
			result += '\n';
		}

		return result;
	}

	void Array2D<CellState>::deserializeBody(std::stringstream& str) {
		for (int y = 0; y < mSize.y; y++) {
			auto line = Serializer::getLine(str);
			if (line.size() != mSize.x)
				throw std::runtime_error("Invalid line length: " + line);

			for (int x = 0; x < mSize.x; x++)
			{
				this->operator[]({ x, y }) = cellFromChar(line[x]);
			}
		}
	}
}
