/******************************************************************************
*
* @author	Maryam Karimi
* @email	mkarimif@uwo.ca
*
* @brief Reminder.cpp gets a username as an input; then opens the corresponding reminder file,
* scans the reminders and saves the ones for current date to a list.
******************************************************************************/

#include "Reminder.h"

/******************************************************************************
* @brief This is the constructor for this class:
* it sets input_file to username_reminders.txt (format of reminders in this project)
* and calls get_reminders.
* @param username: Smart Mirror's user's username
******************************************************************************/
Reminder::Reminder(std::string username){
    input_file = "./";
    input_file.append(REMINDER_DIRECTORY);
    input_file.append("/");
    input_file.append(username);
    input_file.append("_reminders.txt");
    get_reminders();
}

/******************************************************************************
* @brief Reminder class destructor
******************************************************************************/
Reminder::~Reminder(){
}

/******************************************************************************
* @brief get_reminders is a method that opens a reminder file, calls check_line
* on every line of it to compare the dates, and then return an iterator of the list.
* @returns an iterator of the list containing all of the reminders
******************************************************************************/
std::list<std::string>::const_iterator Reminder::get_reminders(){
    std::string line;
    std::ifstream file (input_file);
    if (file.is_open()){
        bool is_first_line = true;
        while (getline(file,line)){
            // skip the first line (only includes titles)
            if (is_first_line){
                is_first_line = false;
            }
            else{
                check_line((char *)line.c_str());
            }
        }
        file.close();
    }
    else{
        reminders.push_front("Unable to open file. Make sure the reminder file name is correct.");
    }

    return reminders.begin();
}

/******************************************************************************
* @brief this method gets a line of form Description,Date(YYYY/MM/DD),Time
* if the date is today, it adds the reminder description and time to the list
* @param line: is a line from reminder file to be checked
******************************************************************************/
void Reminder::check_line(char line[]){
    char *token;

    // split with delimiter "," to get the description
    token = strtok(line,",");
    std::string description(token);

    // split with delimiter "," to get the date
    token = strtok(NULL,",");
    std::string date(token);

    // split with delimiter "," to get the time
    token = strtok(NULL,",");
    std::string time(token);

    // Time is used here to get the cur_date
    Time cur_date;

    if (std::strcmp(date.c_str(),cur_date.get_date().c_str()) == 0){
        std::string today_reminders = "";
        today_reminders.append("Today at ");
        today_reminders.append(time);
        today_reminders.append(" : ");
        today_reminders.append(description);
        reminders.push_front(today_reminders);
    }
}

/******************************************************************************
* @brief getter method for the list of today's reminders
* @returns the list that contains today's reminders
******************************************************************************/
std::list<std::string> Reminder::get_reminder_list(){
    return reminders;
}