
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef EDITOREXCEPTION_HPP
#define EDITOREXCEPTION_HPP

#include <string>



class EditorException
{
public:
    explicit EditorException(const std::string& reason)
        : reason{reason}
    {
    }


    std::string getReason() const
    {
        return reason;
    }


private:
    std::string reason;
};



#endif // EDITOREXCEPTION_HPP

