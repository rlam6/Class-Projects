
// YOU SHOULD NOT NEED TO MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef BOOEDITLOG_HPP
#define BOOEDITLOG_HPP

#include <string>



// booEditLog() writes a single message to the "booedit.log" file, including
// a timestamp (e.g., "2015-11-24 15:58:15") at the beginning of that message.
// You can call this function anywhere you'd like, as a useful tool for letting
// you write debug output to a log file.
void booEditLog(const std::string& message);



#endif // BOOEDITLOG_HPP

