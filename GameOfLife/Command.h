#pragma once

#include <string>

namespace GameOfLife
{
	// Forward declare to avoid circular include
	// We don't need to know anything other than that it exists, as we only use pointers to it
	class Controller;

	class Command
	{
	public:
		virtual ~Command() = default;

		// Execute the command
		virtual void execute(Controller* context) = 0;
	};

	// A factory for creating commands
	class CommandFactory {
	public:
		virtual Command* create(std::string_view input) = 0;
		virtual std::string_view getIdentifier() const = 0;
	};

	// A generic factory for creating commands where a constructor taking a string_view is available
	// By using templates, the compiler can generate the correct implementation for each command with no work on our part
	template <typename T>
	class TypedCommandFactory : public CommandFactory {
		Command* create(std::string_view input) override {
			return new T(input);
		}

		std::string_view getIdentifier() const override {
			return T::Identifier;
		}
	};
}
