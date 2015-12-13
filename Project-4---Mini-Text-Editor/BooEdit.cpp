
// Implementation of the BooEdit class
//
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE INSTRUCTOR - ALEX THRONTON

#include "BooEdit.hpp"
#include "InteractionProcessor.hpp"


void BooEdit::run()
{
    view.start();

    InteractionProcessor processor{model, view, interactionReader};
    processor.run();
}


BooEdit::~BooEdit()
{
    view.stop();
}

