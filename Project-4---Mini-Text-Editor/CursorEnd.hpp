#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"
#include "EditorModel.hpp"

class CursorEnd: public Command
{
public:
	CursorEnd();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	unsigned int oldCursorColumnPosition;

};

#endif // CURSOREND_HPP
