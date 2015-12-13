
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef BOOEDIT_HPP
#define BOOEDIT_HPP

#include "EditorModel.hpp"
#include "EditorView.hpp"
#include "InteractionReader.hpp"



class BooEdit
{
public:
    BooEdit(
        EditorModel& model, EditorView& view,
        InteractionReader& interactionReader)
        : model{model}, view{view}, interactionReader{interactionReader}
    {
    }

    ~BooEdit();

    void run();

private:
    EditorModel& model;
    EditorView& view;
    InteractionReader& interactionReader;
};



#endif // BOOEDIT_HPP

