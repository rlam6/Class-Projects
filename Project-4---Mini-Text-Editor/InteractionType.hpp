
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef INTERACTIONTYPE_HPP
#define INTERACTIONTYPE_HPP



// An "enum class" defines a type that has one of the constant values specified,
// but can't have any other values.  So, in this case, a variable of type
// InteractionType could have the value InteractionType::command,
// InteractionType::undo, and so on.

enum class InteractionType
{
    command,
    undo,
    redo,
    quit
};



#endif // INTERACTIONTYPE_HPP

