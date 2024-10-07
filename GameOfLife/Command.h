#pragma once

#include <string>
#include <memory>

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
		// Construct a command from the given input
		// input will be the entire string after the command identifier,
		// or an empty string if there are no arguments
		virtual std::unique_ptr<Command> create(std::string_view input) = 0;

		// Get the identifier for the command e.g., "help"
		virtual std::string_view getIdentifier() const = 0;
		// Get a one-line summary of the command e.g., "Show available commands or a specific command's usage"
		virtual std::string_view getSummary() const = 0;
		// Get usage information for the command e.g., "help [command]". Typically multiline
		virtual std::string_view getUsage() const = 0;
	};

	// A generic factory for creating commands where a constructor taking a string_view is available
	// By using templates, the compiler can generate the correct implementation for each command with no work on our part
	template <typename T>
	class CommandFactoryImpl : public CommandFactory {
		std::unique_ptr<Command> create(std::string_view input) override {
			return std::make_unique<T>(input);
		}

		std::string_view getIdentifier() const override {
			return T::Identifier;
		}

		std::string_view getSummary() const override {
			return T::Summary;
		}

		std::string_view getUsage() const override {
			return T::Usage;
		}
	};
}
