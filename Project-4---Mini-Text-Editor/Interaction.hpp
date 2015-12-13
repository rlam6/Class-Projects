
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef INTERACTION_HPP
#define INTERACTION_HPP

#include "Command.hpp"
#include "InteractionType.hpp"



class Interaction
{
public:
    static Interaction command(Command* command)
    {
        return Interaction{InteractionType::command, command};
    }

    static Interaction undo() { return Interaction{InteractionType::undo, nullptr}; }
    static Interaction redo() { return Interaction{InteractionType::redo, nullptr}; }
    static Interaction quit() { return Interaction{InteractionType::quit, nullptr}; }

public:
    InteractionType type() const { return type_; }
    Command* command() const { return command_; }

private:
    Interaction(InteractionType type, Command* command)
        : type_{type}, command_{command}
    {
    }

private:
    InteractionType type_;
    Command* command_;
};



#endif // INTERACTION_HPP

