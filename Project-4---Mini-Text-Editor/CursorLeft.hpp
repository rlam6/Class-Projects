#ifndef CURSOR_LEFT_HPP
#define CURSOR_LEFT_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class CursorLeft: public Command
{
public:

	CursorLeft();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Cursor Left Error
	const EditorException cursorLeftError{"Already at beginning"};
};


#endif // CURSOR_LEFT_HPP
