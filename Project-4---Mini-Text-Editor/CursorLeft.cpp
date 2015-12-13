#include "CursorLeft.hpp"
#include "CursorRight.hpp"
#include "EditorModel.hpp"


CursorLeft::CursorLeft()
{

}

void CursorLeft::execute(EditorModel& model){

	// Throw error if already at the beginning of entire text
	if (model.cursorAtBeginningOfLine() && model.cursorAtBeginningOfPage()){
		model.setErrorMessage( cursorLeftError.getReason() );
		throw cursorLeftError;
	}

	// Move cursor up to the end of above line if at the beginning of current line
	else if (model.cursorAtBeginningOfLine()){
		const std::string& previousString = model.line(model.cursorLine()-1);

		model.decrementCursorLine();
		model.setCursorColumn(previousString.length()+1);
	} 

	// Move cursor to the left of current placement
	else{
		model.decrementCursorColumn();
	}
}

void CursorLeft::undo(EditorModel& model){

	// Move cursor right using CursorRight's execute command
	CursorRight cRight;
	cRight.execute(model);
}
