#pragma once

#include "Command.h"

namespace GameOfLife {
    class QuitCommand : public Command
    {
    public:
        static constexpr std::string_view Identifier = "quit";
        static constexpr std::string_view Summary = "Quit the program";
        static constexpr std::string_view Usage = Identifier; // Nothing special to note

        // No arguments are needed for this command
        QuitCommand(std::string_view _args) {}

        void execute(Controller* controller) override;
    };

}