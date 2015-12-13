#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"
#include "EditorModel.hpp"

class CursorHome: public Command
{
public:
	CursorHome();

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:
	unsigned int oldCursorColumnPosition;

};

#endif // CURSORHOME_HPP
