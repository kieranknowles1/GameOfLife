#include "InitCommand.h"

#include <sstream>

#include "Controller.h"
#include "Serializer.h"
#include "Board.h"

namespace GameOfLife {
	InitCommand::InitCommand(std::string_view input)
	{
		std::stringstream stream(input.data());
		mWidth = Serializer::read<int>(stream);
		mHeight = Serializer::read<int>(stream);
		mAliveCells = Serializer::read<int>(stream);
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
