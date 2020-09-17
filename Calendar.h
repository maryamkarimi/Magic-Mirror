/******************************************************************************
*
* @author 	Maryam Karimi
* @email	mkarimif@uwo.ca
*
* @brief header file for Calendar.cpp
*******************************************************************************/

#ifndef CALENDAR_H
#define CALENDAR_H
#include <ctime>
#include <iomanip>
#include <iostream>
#include <string>
#include <list>
#include <iostream>
#include <stdlib.h>

using namespace std;

class Calendar{
private:
    int year, month,day;
    std::string month_name;
    int getNumOfDays(int monthNumber, int year);
    bool isLeapYear(int year);
    int get_first_day(int,int);
public:
    Calendar();
    ~Calendar();
    std::list<std::string> list;
};
#endif