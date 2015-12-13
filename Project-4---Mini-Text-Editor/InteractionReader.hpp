
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef INTERACTIONREADER_HPP
#define INTERACTIONREADER_HPP

#include "Interaction.hpp"



class InteractionReader
{
public:
    virtual ~InteractionReader() = default;
    virtual Interaction nextInteraction() = 0;
};



#endif // INTERACTIONREADER_HPP

