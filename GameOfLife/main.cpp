// GameOfLife.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CommandParser.h"
#include "Controller.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include "Serializer.h"
#include "Experiment/Experiment.h"
#include "Experiment/Pattern.h"

int main()
{
    auto pattern = GameOfLife::Experiment::Pattern();
    auto params = GameOfLife::Experiment::Parameters{
        {30, 30},
        100,
        100,
        100
    };
    auto experiment = GameOfLife::Experiment::Experiment(params, pattern);

    auto result = experiment.run();
    if (result.mSuccess)
    {
        std::cout << "Success! Generation: " << result.mAttempts << "\n";
        std::cout << result.mFinalBoard->toString();
    }

    return 0;

    auto parser = std::make_unique<GameOfLife::CommandParser>();
    GameOfLife::registerDefaultCommands(parser.get());

    // Controller handles the deletion of the parser
    GameOfLife::Controller controller(std::move(parser));

    controller.run();
}