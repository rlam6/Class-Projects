#include "CursorRight.hpp"
#include "CursorLeft.hpp"
#include "EditorModel.hpp"

CursorRight::CursorRight()
{

}

void CursorRight::execute(EditorModel& model){

	// Throw error if already at the end of entire text
	if (model.cursorAtEndOfLine() && model.cursorAtEndOfPage()){
		model.setErrorMessage( cursorRightError.getReason() );
		throw cursorRightError;
	}

	// Place cursor in beginning of next line if currently at the end of a line, but not in the beginning
	else if (model.cursorAtEndOfLine()){
		model.incrementCursorLine();
		model.setCursorColumn(1);
	}

	// Place cursor to the right of current location
	else{
		model.incrementCursorColumn();
	}
}

void CursorRight::undo(EditorModel& model){
	
	// Move cursor left using CursorLeft's execute command
	CursorLeft cLeft;
	cLeft.execute(model);
}
