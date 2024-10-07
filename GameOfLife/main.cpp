// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Board.h"
#include "CommandParser.h"
#include "Controller.h"

int main()
{
    // TODO: Create board through controller
    auto rng = std::mt19937(0);
    auto board = GameOfLife::Board::createRandom({ 10, 10 }, 20, rng);
    std::cout << board.toString();

    auto parser = std::make_unique<GameOfLife::CommandParser>();
    GameOfLife::registerDefaultCommands(parser.get());

    // Controller handles the deletion of the parser
    GameOfLife::Controller controller(std::move(parser));

    controller.run();
}