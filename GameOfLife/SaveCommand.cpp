#include "SaveCommand.h"

#include <filesystem>
#include <iostream>

#include "Controller.h"
#include "Serializer.h"

namespace GameOfLife {
	SaveCommand::SaveCommand(std::string_view args) {
		if (args.empty()) throw InvalidCommandException("Filename must be provided");

		mFilename = args;
	}

	void SaveCommand::execute(Controller* controller) {
		auto fullPath =
			std::filesystem::path(controller->getSaveDirectory())
			/ (mFilename + ".txt");

		std::cout << "Saving to " << std::filesystem::absolute(fullPath) << std::endl;

		auto board = controller->getBoard();
		if (board == nullptr) {
			throw std::runtime_error("No board to save");
		}

		auto file = Serializer::openWrite(fullPath);
		file << Serializer::serialize(*board);
	}
}