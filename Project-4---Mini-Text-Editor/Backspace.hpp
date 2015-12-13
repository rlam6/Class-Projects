#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class Backspace: public Command
{
public:

	Backspace();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Backspace Error
	const EditorException backspaceError{"Already at beginning"};

	// Store the character that will be deleted
	char oldCharacter;

	// Boolean for if the user deleted the beginning of a line
	bool deletedNewLine = false;
};

#endif //BACKSPACE_HPP
