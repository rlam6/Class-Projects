// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "EditorModel.hpp"



class Command
{
public:
    virtual ~Command() = default;

    virtual void execute(EditorModel& model) = 0;
    virtual void undo(EditorModel& model) = 0;
};



#endif // COMMAND_HPP

