
#include "KeypressInteractionReader.hpp"
#include "CursorRight.hpp"
#include "CursorLeft.hpp"
#include "CursorUp.hpp"
#include "CursorDown.hpp"
#include "Character.hpp"
#include "CursorHome.hpp"
#include "CursorEnd.hpp"
#include "Backspace.hpp"
#include "NewLine.hpp"
#include "DeleteLine.hpp"


Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly

            // Command to be put into model as interaction
            Command* c;

            switch (keypress.code())
            {
            // QUIT
            case 'X':
                return Interaction::quit();

            // UNDO / REDO
            case 'Z':
                return Interaction::undo();
            case 'A':
                return Interaction::redo();

            // CURSOR MOVEMENT
            case 'O':
            	c = new CursorRight();
            	return Interaction::command(c);
            case 'U':
            	c = new CursorLeft();
            	return Interaction::command(c);
            case 'I':
                c = new CursorUp();
                return Interaction::command(c);
            case 'K':
                c = new CursorDown();
                return Interaction::command(c);
            case 'Y':
                c = new CursorHome();
                return Interaction::command(c);
            case 'P':
                c = new CursorEnd();
                return Interaction::command(c);

            // BACKSPACE
            case 'H':
                c = new Backspace();
                return Interaction::command(c);

            // NEW LINE INSERT
            case 'J':
                c = new NewLine();
                return Interaction::command(c);
            case 'M':
                c = new NewLine();
                return Interaction::command(c);

            // DELETE LINE
            case 'D':
                c = new DeleteLine();
                return Interaction::command(c);
            }
        }
        else
        {
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly

            // PRINTABLE KEY
            Command* c = new Character(keypress.code());
            return Interaction::command(c);
        }
    }
}

