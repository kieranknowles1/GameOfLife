#include "ShowCommand.h"

#include <iostream>

#include "Controller.h"

namespace GameOfLife {
	void ShowCommand::execute(Controller* controller)
	{
		auto board = controller->getBoard();
		if (board == nullptr) {
			throw std::runtime_error("No board loaded");
		}
		std::cout << board->toString() << std::endl;
	}
}