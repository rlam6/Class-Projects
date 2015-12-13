
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef EDITORVIEW_HPP
#define EDITORVIEW_HPP

#include <string>



class EditorView
{
public:
    virtual ~EditorView() = default;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void refresh() = 0;
};



#endif // EDITORVIEW_HPP

