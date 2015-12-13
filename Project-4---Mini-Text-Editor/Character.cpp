#include "Character.hpp"
#include "EditorModel.hpp"

namespace
{
	// Blank character
	char emtpyChar;
}

Character::Character()
	:characterPressed{emtpyChar}
{

}

Character::Character(const char c)
	:characterPressed{c}
{

}

void Character::execute(EditorModel& model){

	// Place character on line and increment column value for cursor
	model.insert(characterPressed);
	model.incrementCursorColumn();
}

void Character::undo(EditorModel& model){
	// Delete character and decrement column value for cursor
	model.deleteChar();
	model.decrementCursorColumn();
}
