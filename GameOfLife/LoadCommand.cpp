#include "LoadCommand.h"

#include <filesystem>
#include <fstream>
#include <stdexcept>

#include "Controller.h"
#include "Serializer.h"

namespace GameOfLife {
	LoadCommand::LoadCommand(std::string_view args) {
		if (args.empty()) throw std::invalid_argument("Filename must be provided");

		mFilename = args;
	}

	void LoadCommand::execute(Controller* controller) {
		auto fullPath =
			std::filesystem::path(controller->getSaveDirectory())
			/ (mFilename + ".txt");

		auto file = std::ifstream(fullPath);
		if (!file.good()) {
			throw std::runtime_error("Failed to open file for reading");
		}

		auto data = std::string((std::istreambuf_iterator<char>(file)), {});
		auto board = Serializer::deserializeBoard(data);

		controller->setBoard(std::make_unique<Board>(board));
	}
}