#include "SaveCommand.h"

#include <fstream>
#include <filesystem>
#include <iostream>

#include "Controller.h"

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

		auto file = std::ofstream(fullPath);
		if (!file.good()) {
			throw std::runtime_error("Failed to open file for writing");
		}

		auto data = board->serialize();
		file << data;
		// C++ closes files automatically when they go out of scope
	}
}