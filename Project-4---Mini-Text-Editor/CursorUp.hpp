#ifndef CURSOR_UP_HPP
#define CURSOR_UP_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class CursorUp: public Command
{
public:

	CursorUp();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Cursor Up Error
	const EditorException cursorUpError{"Already at top"};

	// Old column placement stored
	unsigned int oldColumnNum;
};


#endif //CURSOR_UP_HPP
