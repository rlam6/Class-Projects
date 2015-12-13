#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"
#include "EditorModel.hpp"

class NewLine : public Command
{
public:
	NewLine()
	{

	}

    virtual void execute(EditorModel& model);

    virtual void undo(EditorModel& model);

private:
	int oldColumnNum = 1;
	bool addedFromMiddle = false;
};

#endif //NEWLINE_HPP
