/******************************************************************************
*
* @author   Maryam Karimi
* @email 	mkarimif@uwo.ca
*
* @headerfile This is the header file for Reminder.cpp
******************************************************************************/

#ifndef GROUP6_REMINDER_H
#define GROUP6_REMINDER_H

#define REMINDER_DIRECTORY "Reminders" // the directory that reminder txt's are saved in

#include <fstream>
#include <string>
#include <cstring>
#include <list>
#include <iterator>

#include "Time.h"

class Reminder{

private:
    std::string input_file;
    std::list<std::string> reminders;
    void check_line(char[]);
public:
    Reminder(std::string); // input is the reminder text file that this class reads from (e.g reminder.txt)
    ~Reminder();
    std::list<std::string>::const_iterator get_reminders();
    std::list<std::string> get_reminder_list();
};

#endif //GROUP6_REMINDER_H
