#include "InitCommand.h"

#include <sstream>

#include "Controller.h"
#include "Board.h"

namespace GameOfLife {
	InitCommand::InitCommand(std::string_view input)
	{
		std::stringstream stream(input.data());
		stream >> mWidth >> mHeight >> mAliveCells;

		// Make sure everything was read
		if (stream.fail())
		{
			throw std::invalid_argument("Invalid args");
		}
	}

	void InitCommand::execute(Controller* context)
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		auto board = std::make_unique<Board>(Vec2(mWidth, mHeight));
		board->fillRandom(mAliveCells, gen);

		context->setBoard(std::move(board));
	}
}