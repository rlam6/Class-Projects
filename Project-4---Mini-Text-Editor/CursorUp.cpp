#include "CursorUp.hpp"
#include "EditorModel.hpp"

namespace
{
	const std::string emptyString = "";
	const unsigned int defaultColumnNum = 1;
}

CursorUp::CursorUp()
	:oldColumnNum{defaultColumnNum}
{

}

void CursorUp::execute(EditorModel& model){

	// Assign old column number to current column
	oldColumnNum = model.cursorColumn();

	// Throw error if already at the top of page
	if (model.cursorAtBeginningOfPage()){
		model.setErrorMessage( cursorUpError.getReason() );
		throw cursorUpError;
	}

	// Index of column cursor
	const int currentColumnNum = model.cursorColumn()-1;
	const std::string& previousLine = model.line(model.cursorLine()-1);
	const bool previousLineTooShort = currentColumnNum > previousLine.length()-1;

	// Decrement the cursor line placement and set column placement to be end of line if previous line
	if(previousLineTooShort || previousLine == emptyString){
		model.decrementCursorLine();
		model.setCursorColumn(previousLine.length()+1);
	}

	// Decrement the cursor line placement
	else{
		model.decrementCursorLine();
	}
}

void CursorUp::undo(EditorModel& model){
	
	// Set column placement to previously stored one, increment line placement
	model.setCursorColumn(oldColumnNum);
	model.incrementCursorLine();
}
