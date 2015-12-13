
// Implementation of the InteractionProcessor class

#include <vector>
#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"

// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    view.refresh();

    std::vector<Command*> undoList;
    std::vector<Command*> redoList;

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if (not undoList.empty()){
                try{
                    Command* lastUndoCommand = undoList.back();
                    lastUndoCommand->undo(model);
                    model.clearErrorMessage();

                    redoList.push_back(lastUndoCommand);
                    undoList.pop_back();

                    view.refresh();
                }
                catch (EditorException& e)
                {
                    model.setErrorMessage(e.getReason());
                }
            }
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (not redoList.empty()){
                try{
                    Command* lastRedoCommand = redoList.back();
                    lastRedoCommand->execute(model);
                    model.clearErrorMessage();

                    undoList.push_back(lastRedoCommand);
                    redoList.pop_back();

                    view.refresh();
                }
                catch (EditorException& e)
                {
                    model.setErrorMessage(e.getReason());
                }
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                model.clearErrorMessage();

                if (not redoList.empty()){
                    for (int i = 0; i < redoList.size(); i++){
                        delete redoList.at(i);
                    }
                    redoList.clear();
                }
                undoList.push_back(command);
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
                delete command;
            }


            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
            // delete command;
        }
    }
    for (int i = 0; i < redoList.size(); i++){
        delete redoList.at(i);
    }
    for (int i = 0; i < undoList.size(); i++){
        delete undoList.at(i);
    }
}

