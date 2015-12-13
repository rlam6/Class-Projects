#ifndef CURSOR_DOWN_HPP
#define CURSOR_DOWN_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class CursorDown: public Command
{
public:

	CursorDown();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Cursor Down Error
	const EditorException cursorDownError{"Already at bottom"};

	// Old column position for cursor prior to moving down
	unsigned int oldColumnNum;
};


#endif //CURSOR_DOWN_HPP
