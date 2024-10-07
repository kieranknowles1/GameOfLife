#pragma once

#include <string>

namespace GameOfLife
{
	class Command
	{
	public:
		virtual ~Command() = default;

		// Execute the command
		// TODO: Take something as a context. Maybe the controller?
		virtual void execute() = 0;
	};

	// A factory for creating commands
	class CommandFactory {
	public:
		virtual Command* create(std::string_view input) = 0;
		virtual std::string_view getIdentifier() const = 0;
	};

	// A generic factory for creating commands where a constructor taking a string_view is available
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
