#include "CursorDown.hpp"
#include "EditorModel.hpp"

namespace
{
	const unsigned int defaultColumnNum = 1;
	const std::string emptyString = "";
}

CursorDown::CursorDown()
	:oldColumnNum{defaultColumnNum}
{

}

void CursorDown::execute(EditorModel& model){

	// Set old column number to be the current column position
	oldColumnNum = model.cursorColumn();


	// Throw error if already at the bottom of the page
	if (model.cursorAtEndOfPage()){
		model.setErrorMessage( cursorDownError.getReason() );
		throw cursorDownError;
	}

	// Initialize helper variables for cursor column positioning
	const int currentColumnNum = model.cursorColumn()-1;
	const std::string& nextLine = model.line(model.cursorLine()+1);
	const bool nextLineTooShort = currentColumnNum > nextLine.length()-1;

	// Set cursor to end of line if next line cursor is going to palced in is too short
	if(nextLineTooShort || nextLine == emptyString){
		model.incrementCursorLine();
		model.setCursorColumn(nextLine.length()+1);
	}

	// Move cursor down one line, keep column position
	else{
		model.incrementCursorLine();
	}
}

void CursorDown::undo(EditorModel& model){

	// Move cursor back to old column positioning, move up one line
	model.setCursorColumn(oldColumnNum);
	model.decrementCursorLine();
}
