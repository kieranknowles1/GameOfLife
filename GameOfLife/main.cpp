// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CommandParser.h"
#include "Controller.h"

int main()
{
    auto parser = std::make_unique<GameOfLife::CommandParser>();
    GameOfLife::registerDefaultCommands(parser.get());

    // Controller handles the deletion of the parser
    GameOfLife::Controller controller(std::move(parser));

    controller.run();
}