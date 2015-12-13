#ifndef DELETE_LINE_HPP
#define DELETE_LINE_HPP

#include "Command.hpp"
#include "EditorModel.hpp"
#include "EditorException.hpp"

class DeleteLine: public Command
{
public:

	DeleteLine();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	// Delete line error
	const EditorException deleteLineError{"Already empty"};

	// Deleted line's string of text
	std::string oldString;

	// These are the deleted line's cursor and line count information
	int lineNumber;
	int cursorPos;
	int lineCount;
};

#endif //DELETE_LINE_HPP
