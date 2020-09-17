/******************************************************************************
*
* @author 	Maryam Karimi
* @email	mkarimif@uwo.ca
*
* @brief Time.cpp class gets the local time and date
******************************************************************************/

#include "Time.h"

/******************************************************************************
* @brief the constructor for this class: it initializes time and date by calling
* initialize_time and initialize_date.
******************************************************************************/
Time::Time(){
    initialize_time();
    initialize_date();
};

/******************************************************************************
* @brief Time class destructor
******************************************************************************/
Time::~Time(){
}

/******************************************************************************
* @brief this method initializes cur_time.
* It gets the raw time by calling time(0), then uses put_time
* to get the current time with the format specified. (TIME_FORMAT: can be changed
* in the header file). It's saved into a string buffer initially and the casted
* to string.
******************************************************************************/
void Time::initialize_time(){
    time_t raw_time = time(0);
    std::stringstream str_stream;
    str_stream << std::put_time(localtime(&raw_time), TIME_FORMAT);
    cur_time = str_stream.str();
}


/******************************************************************************
* @brief this method initializes cur_date.
* It gets the raw time by calling time(0), then uses put_time
* to get the current date with the format specified. (DATE_FORMAT: can be changed
* in the header file). It's saved into a string buffer initially and the casted
* to string.
******************************************************************************/
void Time::initialize_date(){
    time_t raw_time = time(0);
    std::stringstream str_stream;
    str_stream << std::put_time(localtime(&raw_time), DATE_FORMAT);
    cur_date = str_stream.str();
}


/******************************************************************************
* @brief this is a getter method for time.
* @returns cur_time: the current time as a string of format TIME_FORMAT
******************************************************************************/
std::string Time::get_time(){
    initialize_time();
    return cur_time;
}

/******************************************************************************
* @brief this is a getter method for date.
* @returns cur_date: the current date as a string of format DATE_FORMAT
******************************************************************************/
std::string Time::get_date(){
    initialize_date();
    return cur_date;
}