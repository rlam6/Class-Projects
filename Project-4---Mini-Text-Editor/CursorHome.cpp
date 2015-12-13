#include "CursorHome.hpp"

namespace
{
	const unsigned int firstColumnPosition = 1;
}

CursorHome::CursorHome()
	:oldCursorColumnPosition{firstColumnPosition}
{

}

void CursorHome::execute(EditorModel& model){

	// Store old cursor column position
	oldCursorColumnPosition = model.cursorColumn();

	// Set current column position of cursor to the beginning of the line
	model.setCursorColumn(firstColumnPosition);
}

void CursorHome::undo(EditorModel& model){
	
	// Move cursor back to former position
	model.setCursorColumn(oldCursorColumnPosition);
}
