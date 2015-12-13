#include "DeleteLine.hpp"
#include "EditorModel.hpp"
#include "CursorUp.hpp"

namespace
{
	const std::string emptyString = "";
	const int firstLine = 1;
}

DeleteLine::DeleteLine()
	:oldString{""}, lineNumber{1}, cursorPos{1}
{

}

void DeleteLine::execute(EditorModel& model){
	
	// Obtain previous values of pre-deletion for line
	oldString = model.line(model.cursorLine());
	lineNumber = model.cursorLine();
	cursorPos = model.cursorColumn();
	lineCount = model.lineCount();

	// Throw error if text is empty
	if (lineNumber == firstLine && model.line(lineNumber) == emptyString && model.lineCount() == 1){
		model.setErrorMessage( deleteLineError.getReason() );
		throw deleteLineError;
	}

	// Empty the first line if that is the only line in the text (there should be at least one line in the text)
	if (model.lineCount() == firstLine){
		model.setLineString(firstLine, emptyString);
		model.setCursorColumn(1);
	}

	// Delete the line and move the curser up if you are at the end of the page
	else{
		// Set boolean variables for cursor line placement
		const bool atBeginningOfPage = model.cursorAtBeginningOfPage();
		const bool atEndOfPage = model.cursorAtEndOfPage();
		const bool previousColumnPlacementTooFar = model.cursorColumn() > model.line(model.cursorLine()).length();

		// Only initialize this boolean if you are not at the end of the page
		const bool nextColumnPlacementTooFar = !atEndOfPage ? model.cursorColumn() > model.line(model.cursorLine()+1).length() : false;

		// Deletes current line from text
		model.deleteLine(model.cursorLine());

		// Move cursor up if at the end of the page
		if (atEndOfPage){
			CursorUp c;
			c.execute(model);
		}

		// Fix cursor column placement if cursor is at the beginning of text, 
		else if (atBeginningOfPage && previousColumnPlacementTooFar){
			model.setCursorColumn(model.line(model.cursorLine()).length()+1);
		}
		else if (nextColumnPlacementTooFar){
			model.setCursorColumn(model.line(model.cursorLine()).length()+1);
		}
		// Decrement the current line count
		model.decrementLineCount();
	}
}

void DeleteLine::undo(EditorModel& model){

	// Handling deletion of line if cursor is not in the first line
	if(lineNumber != firstLine){
		model.insertString(lineNumber, oldString);
		model.incrementLineCount();	

		// If previous line was at the end of the text
		if(lineNumber == model.lineCount()){
			model.incrementCursorLine();
		}
	}

	// Handling deletion of first line of text
	else{

		// If first line contained either empty string or was not the last line of text
		if (oldString == emptyString || lineCount != 1){
			model.incrementLineCount();
			model.insertString(lineNumber, oldString);
		} 

		// Initializes first line of text if it was the only line left
		else{
			model.setLineString(lineNumber, oldString);
		}
	}

	// Fix cursor positioning
	model.setCursorColumn(cursorPos);
}
