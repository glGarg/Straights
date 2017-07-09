#ifndef _COMMAND_
#define _COMMAND_

#include "Card.h"
#include <istream>


struct Command
{
public:
	enum class Type
	{
		PLAY,
		DISCARD,
		DECK,
		QUIT,
		RESTART,
		RAGEQUIT,
		BAD_COMMAND\
	};

	Type type;
	Card card;

	Command();
	// Ensures: Command is set to invalid state, card is set to AC

	class CommandException
	{
	public:
		CommandException(const std::string);
		std::string what() const;
	private:
		const std::string message_;
	};

	class IllegalCommandException : public CommandException
	{
	public:
		IllegalCommandException(std::string);
	};
};

std::istream & operator>>(std::istream&, Command&);
// Modifies: input stream and Command
// Ensures: Command is set to a valid command and has its associated card argument
// Throws: fails assertion if unable to read in a valid command and its associated card argument,
//    if applicable.
// Returns: input stream

#endif
