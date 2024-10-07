#pragma once

#include "CommandParser.hpp"

namespace GameOfLife
{
	class Control
	{
	public:
		Control();

	private:
		Commands::CommandParser parser;
	};
}