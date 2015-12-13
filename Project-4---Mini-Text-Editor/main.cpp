
// THIS FILE BELONGS TO THE ICS45C INSTRUCTOR - ALEX THORNTON

#include <csignal>
#include <sstream>
#include "BooEdit.hpp"
#include "BooEditLog.hpp"
#include "EditorModel.hpp"
#include "KeypressInteractionReader.hpp"
#include "NcursesEditorView.hpp"
#include "NcursesKeypressReader.hpp"



namespace
{
    BooEdit* booEdit = nullptr;
    EditorModel model;
    NcursesEditorView view{model};
    NcursesKeypressReader keypressReader;
    KeypressInteractionReader interactionReader{keypressReader};


    void logStarted(const std::string& programName)
    {
        std::ostringstream oss;
        oss << "Started " << programName;
        
        booEditLog(oss.str());
    }


    void logStopped(const std::string& programName)
    {
        std::ostringstream oss;
        oss << "Stopped " << programName;

        booEditLog(oss.str());
    }


    void startBooEdit()
    {
        booEdit = new BooEdit{model, view, interactionReader};
        booEdit->run();
    }


    void stopBooEdit()
    {
        if (booEdit != nullptr)
        {
            delete booEdit;
            booEdit = nullptr;
        }
    }


    int signals[6] { SIGTERM, SIGSEGV, SIGILL, SIGINT, SIGABRT, SIGFPE };


    void unregisterSignalHandlers()
    {
        for (int signal : signals)
        {
            std::signal(signal, SIG_DFL);
        }
    }


    void signalHandler(int signum)
    {
        unregisterSignalHandlers();
        stopBooEdit();
    }


    void registerSignalHandlers()
    {
        for (int signal : signals)
        {
            std::signal(signal, signalHandler);
        }
    }
}

#include <vector>
#include <iostream>

int main(int argc, char** argv)
{
    std::string programName{argv[0]};

    try
    {
        logStarted(programName);

        registerSignalHandlers();
        startBooEdit();

        unregisterSignalHandlers();
        stopBooEdit();

        logStopped(programName);
    }
    catch (...)
    {
        unregisterSignalHandlers();
        stopBooEdit();

        logStopped(programName);

        throw;
    }

    return 0;
}


