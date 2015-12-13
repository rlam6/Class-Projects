#include "Backspace.hpp"
#include "EditorModel.hpp"

namespace
{
	char blankChar;
	const bool isFalse = false;
	const int firstColumn = 1;
}

Backspace::Backspace()
	:oldCharacter{blankChar}, deletedNewLine{isFalse}
{

}

void Backspace::execute(EditorModel& model){


	// If at the beginning of entire page, throw an error
	if (model.cursorAtBeginningOfPage() && model.cursorAtBeginningOfLine()){
		model.setErrorMessage( backspaceError.getReason() );
		throw backspaceError;
	}


	// If at the beginning of a line but not at the beginning of the page, then delete that entire line and append leftover string to above line
	else if (model.cursorAtBeginningOfLine()){

		// New column number
		const int newColumnNum = model.line(model.cursorLine()-1).length()+1;

		// Boolean if cursor is on the middle of the page
		const bool atMiddleOfPage = model.cursorLine() != model.lineCount();

		// Delete special case of line in the middle of the page
		if (atMiddleOfPage){
			model.deleteNewLineInMiddle();
		}

		// Delete the new line
		else{
			model.deleteNewLine();
		}

		// Decrement line count, line placement, and set new cursor column
		model.decrementCursorLine();
		model.decrementLineCount();
		model.setCursorColumn(newColumnNum);

		// Set this true since you deleted a new line
		deletedNewLine = true;
	}


	// Delete the character and store the old character inside the object
	else{
		oldCharacter = model.line(model.cursorLine()).at(model.cursorColumn()-2);
		model.deleteChar();
		model.decrementCursorColumn();
	}
}

void Backspace::undo(EditorModel& model){

	// If you deleted a new line, run this
	if (deletedNewLine){

		// Boolean if cursor is on the middle of the page
		const bool atMiddleOrBeginningOfPage = model.cursorLine() < model.lineCount();

		// Add a line in the middle of the page if cursor is at the middle
		if (atMiddleOrBeginningOfPage){
			model.addNewLineInMiddle();
		}

		// Insert a new line elsewhere
		else{
			model.insertNewLine();
		}

		// Increment line position, line count, and set new cursor position to the first column
		model.incrementCursorLine();
		model.incrementLineCount();
		model.setCursorColumn(firstColumn);
	}


	// Just insert the old character back to the page, increment column position
	else{
		model.insert(oldCharacter);
		model.incrementCursorColumn();
	}
}
