
#ifndef EDITORMODEL_HPP
#define EDITORMODEL_HPP

#include <string>
#include <vector>



class EditorModel
{
public:
    // Initializes the editor model.  Initially, the cursor is on
    // line 1 column 1 and there should be one empty line of text
    // in the editor.
    EditorModel();

    // Returns the line number where the cursor currently should reside.
    int cursorLine() const;

    // Returns the column number where the cursor currently should reside.
    int cursorColumn() const;

    // Returns the number of lines of text currently in the editor.
    int lineCount() const;

    // Returns the text on the given line number.
    const std::string& line(int lineNumber) const;

    // Returns the error message that should be displayed currently.
    const std::string& currentErrorMessage() const;

    // Sets the error message that should be displayed currently.
    void setErrorMessage(const std::string& error);

    // Clears the error message that should be displayed currently.
    void clearErrorMessage();

    // CURSOR BOOLEAN FUNCTIONS
    bool cursorAtBeginningOfLine() const;

    bool cursorAtBeginningOfPage() const;

    bool cursorAtEndOfLine() const;

    bool cursorAtEndOfPage() const;

    // STRING HANDLING FUNCTIONS
    void setLineString(const int lineNumber, const std::string& newString);

    // INSERT HANDLING FUNCTIONS
    void insert(const char c);

    void insertString(const int lineNumber, const std::string& newString);

    void insertNewLine();

    void addNewLineInMiddle();

    // DELETE HANDLING FUNCTIONS
    void deleteNewLine();

    void deleteNewLineInMiddle();

    void deleteChar();

    void deleteLine(const int lineNumber);

    // COLUMN HANDLING FUNCTIONS
    void setCursorColumn(const int n);

    void incrementCursorColumn();

    void decrementCursorColumn();

    // LINE HANDLING FUNCTIONS
    void incrementCursorLine();

    void decrementCursorLine();

    // LINE COUNT HANDLING FUNCTIONS
    void incrementLineCount();

    void decrementLineCount();

private:
    // Write declarations for any private member variables here.
    // Additionally, you can add any private member functions you'd like.

    // Keeps cursor position in terms of column, line, and number of lines intext
	int columnPosition;
	int linePosition;
	int countLine;

    // Text model's error message
	std::string errorMessage;

    // List of all the text to be placed inside text model
    std::vector< std::string > text;
};



#endif // EDITORMODEL_HPP

