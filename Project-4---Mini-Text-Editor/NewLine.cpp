#include "NewLine.hpp"

void NewLine::execute(EditorModel& model){

	// Assign old column number to the current column number before adding new line
	oldColumnNum = model.cursorColumn();


	// If cursor is at the end of the page, add the new line and move the cursor to the right place
	if (model.cursorAtEndOfPage()){
		model.insertNewLine();
		model.incrementCursorLine();
		model.incrementLineCount();
		model.setCursorColumn(1);
	}

	// If the cursor is in the middle or beginning, add the new line and move everything else down
	else{
		addedFromMiddle = true;
		model.addNewLineInMiddle();
		model.incrementCursorLine();
		model.incrementLineCount();
		model.setCursorColumn(1);
	}
}

void NewLine::undo(EditorModel& model){

	// If you added a newline from the middle, delete that new line
	if (addedFromMiddle){
		model.deleteNewLineInMiddle();
	}

	// IF you added that newline from the end, delete that new line with this function
	else{
		model.deleteNewLine();
	}

	// Move the cursor in the right place
	model.decrementCursorLine();
	model.decrementLineCount();
	model.setCursorColumn(oldColumnNum);
}
