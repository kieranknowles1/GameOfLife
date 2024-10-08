// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CommandParser.h"
#include "Controller.h"

// TODO: Temporary
#include <fstream>
#include "Serializer.h"

int main()
{
    auto parser = std::make_unique<GameOfLife::CommandParser>();
    GameOfLife::registerDefaultCommands(parser.get());

    // Controller handles the deletion of the parser
    GameOfLife::Controller controller(std::move(parser));

    auto file = std::ifstream("./save/test.txt");
    auto data = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    auto board = GameOfLife::Serializer::deserialize(data);
    std::cout << board.toString() << std::endl;

    controller.run();
}