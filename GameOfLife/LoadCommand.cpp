#include "LoadCommand.h"

#include <filesystem>
#include <stdexcept>

#include "Controller.h"
#include "Serializer.h"

namespace GameOfLife {
	LoadCommand::LoadCommand(std::string_view args) {
		if (args.empty()) throw std::invalid_argument("Filename must be provided");

		mFilename = args;
	}

	void LoadCommand::execute(Controller* controller) {
		auto data = Serializer::readFile(std::string(controller->getSaveDirectory()) + mFilename + ".txt");
		auto board = Serializer::deserializeBoard(data);

		controller->setBoard(std::make_unique<Board>(board));
	}
}