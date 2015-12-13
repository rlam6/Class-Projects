
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef KEYPRESSREADER_HPP
#define KEYPRESSREADER_HPP

#include "Keypress.hpp"



class KeypressReader
{
public:
    virtual ~KeypressReader() = default;
    virtual Keypress nextKeypress() = 0;
};



#endif // KEYPRESSREADER_HPP

