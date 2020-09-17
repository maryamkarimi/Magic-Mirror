/******************************************************************************
*
* Name: 	Maryam Karimi
* Email: 	mkarimif@uwo.ca
*
* @headerfile this is the header file for Time.cpp
******************************************************************************/

#ifndef GROUP6_TIME_H
#define GROUP6_TIME_H

#define TIME_FORMAT "%I:%M %p" // e.g. 12:21 PM
#define DATE_FORMAT "%Y/%m/%d" // e.g. 2018/11/27

#include <ctime>
#include <iomanip>
#include <string>

class Time{
private:
    std::string cur_time;
    std::string cur_date;

    void initialize_time();
    void initialize_date();

public:
    Time();
    ~Time();
    std::string get_time();
    std::string get_date();
};

#endif //GROUP6_TIME_H
