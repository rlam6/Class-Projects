#ifndef CHARACTERPRESS_HPP
#define CHARACTERPRESS_HPP

#include "Command.hpp"
#include "EditorModel.hpp"

class Character: public Command
{
public:
	Character();

	Character(const char c);

	virtual void execute(EditorModel& model);

	virtual void undo(EditorModel& model);

private:

	// Store the character that the user pressed
	char characterPressed;
};

#endif //CHARACTERPRESS_HPP
