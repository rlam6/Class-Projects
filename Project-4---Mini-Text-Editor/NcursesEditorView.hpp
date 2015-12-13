
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef NCURSESEDITORVIEW_HPP
#define NCURSESEDITORVIEW_HPP

#include "EditorModel.hpp"
#include "EditorView.hpp"



class NcursesEditorView : public EditorView
{
public:
    explicit NcursesEditorView(EditorModel& model);

    virtual void start();
    virtual void stop();
    virtual void refresh();

private:
    EditorModel& model;

    int topVisibleLine;
    int leftVisibleColumn;
};



#endif // NCURSESEDITORVIEW_HPP

