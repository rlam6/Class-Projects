
#include "EditorModel.hpp"
#include "EditorException.hpp"



// EDITOR MODEL ONSTRUCTOR
EditorModel::EditorModel()
	:columnPosition{1}, linePosition{1}, countLine{1}, text{{}}
{
	// Initialize index 0 of text to be empty (index 0 is not shown in text)
	text.push_back("");	
}




// CURSOR AND LINE COUNT INFORMATION RETURN FUNCTIONS
int EditorModel::cursorLine() const
{
	// Returns current line position of cursor
    return linePosition;
}


int EditorModel::cursorColumn() const
{
	// Returns current column position of cursor
    return columnPosition;
}


int EditorModel::lineCount() const
{
	// Returns number of lines in text
    return countLine;
}





// CURSOR BOOLEAN FUNCTIONS	
bool EditorModel::cursorAtBeginningOfLine() const{
	return this->cursorColumn() == 1;
}

bool EditorModel::cursorAtBeginningOfPage() const{
	return this->cursorLine() == 1;
}

bool EditorModel::cursorAtEndOfLine() const{
	return this->cursorColumn() > this->line(this->cursorLine()).length();
}

bool EditorModel::cursorAtEndOfPage() const{
	return this->cursorLine() == this->lineCount();
}





// LINE RETURNING FUNCTION
const std::string& EditorModel::line(int lineNumber) const
{
	// Returns the specified line of text
	return text.at(lineNumber);
}





// TEXT MODEL ERROR FUNCTIONS
const std::string& EditorModel::currentErrorMessage() const
{
	// Returns error message to be displayed by window
    return errorMessage;
}


void EditorModel::setErrorMessage(const std::string& error)
{
	// Assigns what the error message for window should be
	errorMessage = error;
}


void EditorModel::clearErrorMessage()
{
	// Clears error message by window
	errorMessage = "";
}




// COLUMN HANDLING FUNCTIONS
void EditorModel::setCursorColumn(const int n){
	// Assigns new column position for cursor
	columnPosition = n;
}

void EditorModel::incrementCursorColumn(){
	// Increments column position for cursor
	columnPosition++;
}

void EditorModel::decrementCursorColumn(){
	// Decrements column position for cursor
	columnPosition--;
}





// LINE HANDLING FUNCTIONS
void EditorModel::incrementCursorLine(){
	// Increments line position for cursor
	linePosition++;
}

void EditorModel::decrementCursorLine(){
	// Decrements line position for cursor
	linePosition--;
}




// LINE COUNT HANDLING FUNCTIONS
void EditorModel::incrementLineCount(){
	// Increments number of lines in text
	countLine++;
}


void EditorModel::decrementLineCount(){
	// Decreents number of lines in text
	countLine--;
}




// INSERT HANDLING FUNCTIONS
void EditorModel::insert(const char c){

	// Initialize variables concerning text
	const int currentColumnNum = cursorColumn()-1;
	const int currentLineNum = cursorLine();

	const std::string& currentString = text.at(currentLineNum);
	const int currentLineLen = currentString.length();


	// String of text before cursor
	std::string beforeCursor = currentString.substr(0, currentColumnNum);
	// String of text after cursor
	std::string afterCursor = currentString.substr(currentColumnNum, currentLineLen);
	// New string created from inserting new character
	std::string newString = beforeCursor + c + afterCursor;

	// Assign line of text to new string created
	text.at(currentLineNum) = newString;
}

void EditorModel::insertNewLine(){
	// Initialize variables concerning text
	const int currentColumnNum = cursorColumn()-1;
	const int currentLineNum = cursorLine();

	const std::string& currentString = text.at(currentLineNum);
	const int currentLineLen = currentString.length();

	// String of text before cursor
	std::string beforeCursor = currentString.substr(0, currentColumnNum);
	// String of text after cursor
	std::string afterCursor = currentString.substr(currentColumnNum, currentLineLen);

	// Assigns previous line to string of text before cursor, adds text after cursor to new line
	text.at(currentLineNum) = beforeCursor;
	text.push_back(afterCursor);
}

void EditorModel::addNewLineInMiddle(){
	// Initialize variables concerning text
	const int currentColumnNum = cursorColumn()-1;
	const int currentLineNum = cursorLine();

	const std::string& currentString = text.at(currentLineNum);
	const int currentLineLen = currentString.length();

	std::string beforeCursor = currentString.substr(0, currentColumnNum);			  // This is the string left behind
	std::string afterCursor = currentString.substr(currentColumnNum, currentLineLen); // This is the string that gets put in new line

	// Sets line position to add new line
	std::vector<std::string>::iterator linePosition;
	linePosition = text.begin()+cursorLine()+1;

	// Assign new line to text
	text.at(currentLineNum) = beforeCursor;
	text.insert(linePosition, afterCursor);
}





// DELETE HANDLING FUNCTIONS
void EditorModel::deleteNewLine(){
	// Initialize variables concerning text
	const int currentLineNum = cursorLine();

	// Gets line of text to be removed
	const std::string& currentString = text.at(currentLineNum);

	// Add line of text to previous line, delete current one
	text.at(currentLineNum-1) += currentString;
	text.pop_back();
}

void EditorModel::deleteNewLineInMiddle(){
	// Initialize variables concerning text
	const int currentLineNum = cursorLine();

	// Gets line of text to be removed from the middle
	const std::string& currentString = text.at(currentLineNum);

	// Add line of text to previous line, delete current one from the middle
	text.at(currentLineNum-1) += currentString;
	text.erase(text.begin() + currentLineNum);
}

void EditorModel::deleteChar(){
	// Initialize variables concerning text
	const int currentColumnNum = cursorColumn()-1;
	const int currentLineNum = cursorLine();

	// Get current line of string to be worked with
	const std::string& currentString = text.at(currentLineNum);
	const int currentLineLen = currentString.length();

	// Get two strings of text from before and after cursor
	std::string beforeCursor = currentString.substr(0, currentColumnNum-1);
	std::string afterCursor = currentString.substr(currentColumnNum, currentLineLen);

	// Assign line of text to new string without deleted character
	text.at(currentLineNum) = beforeCursor + afterCursor;
}

void EditorModel::deleteLine(const int lineNumber){
	// Deletes line of text
	text.erase(text.begin() + lineNumber);
}






// STRING HANDLING FUNCTIONS
void EditorModel::setLineString(const int lineNumber, const std::string& newString){
	// Assigns line of text to a new specific string
	text.at(lineNumber) = newString;
}

void EditorModel::insertString(const int lineNumber, const std::string& newString){
	// Inserts new string into text
	text.insert(text.begin() + lineNumber, newString);
}
