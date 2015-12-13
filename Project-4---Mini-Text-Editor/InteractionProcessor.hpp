
#ifndef INTERACTIONPROCESSOR_HPP
#define INTERACTIONPROCESSOR_HPP

#include "EditorModel.hpp"
#include "EditorView.hpp"
#include "InteractionReader.hpp"



class InteractionProcessor
{
public:
    InteractionProcessor(
        EditorModel& model, EditorView& view,
        InteractionReader& interactionReader)
        : model{model}, view{view}, interactionReader{interactionReader}
    {
    }

    void run();

private:
    EditorModel& model;
    EditorView& view;
    InteractionReader& interactionReader;
};



#endif // INTERACTIONPROCESSOR_HPP

