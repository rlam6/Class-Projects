#ifndef CURSOR_RIGHT_HPP
#define CURSOR_RIGHT_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class CursorRight: public Command
{
public:

	CursorRight();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Cursor Right Error
	const EditorException cursorRightError{"Already at end"};
};


#endif // CURSOR_RIGHT_HPP
