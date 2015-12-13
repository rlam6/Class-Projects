
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef NCURSESKEYPRESSREADER_HPP
#define NCURSESKEYPRESSREADER_HPP

#include "KeypressReader.hpp"



class NcursesKeypressReader : public KeypressReader
{
public:
    virtual Keypress nextKeypress();
};



#endif // NCURSESKEYPRESSREADER_HPP

