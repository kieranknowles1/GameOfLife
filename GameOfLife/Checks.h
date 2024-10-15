#pragma once

#include <stdexcept>
#include <sstream>

namespace GameOfLife
{
	// Class for asserting conditions are met
	// If a condition is not met, std::invalid_argument is thrown
	class Checks
	{
	private:
		Checks() = delete;
	public:
		// Check that a stream is OK
		static void streamOk(const std::stringstream& stream, const std::string& message)
		{
			if (stream.fail())
			{
				throw std::invalid_argument(message);
			}
		}
	};
}

