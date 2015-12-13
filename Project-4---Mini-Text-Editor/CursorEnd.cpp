#include "CursorEnd.hpp"

namespace
{
	const unsigned int firstColumnPosition = 1;
}

CursorEnd::CursorEnd()
	:oldCursorColumnPosition{firstColumnPosition}
{

}

void CursorEnd::execute(EditorModel& model){
	// Set old column position to be current position
	oldCursorColumnPosition = model.cursorColumn();
	const std::string& currentString = model.line(model.cursorLine());

	// Move cursor to the end of the line
	model.setCursorColumn(currentString.length()+1);
}

void CursorEnd::undo(EditorModel& model){

	// Move cursor back to former position
	model.setCursorColumn(oldCursorColumnPosition);
}
