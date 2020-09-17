/******************************************************************************
*
* @author 	Maryam Karimi
* @email	mkarimif@uwo.ca
*
******************************************************************************/

#include "Calendar.h"

const int WEEK = 7;  // used for modular division
const int MIN_DAYS = 28;  // minimum number of days in a month

/******************************************************************************
 * @brief the constructor for this class:
 * it adds the info for a calendar to a list which is then used by CalendarUI.cpp
******************************************************************************/
Calendar::Calendar(){

    /// @author Maryam Karimi
    time_t raw_time = time(0);
    tm* now = localtime(&raw_time);

    // initialize year
    std::stringstream str_stream;
    str_stream << std::put_time(localtime(&raw_time), "%Y");
    year = atoi(str_stream.str().c_str());

    // initialize month
    std::stringstream str_stream1;
    str_stream1 << std::put_time(localtime(&raw_time), "%m");
    month = atoi(str_stream1.str().c_str());

    // initialize month
    std::stringstream str_stream2;
    str_stream2 << std::put_time(localtime(&raw_time), "%d");
    day = atoi(str_stream2.str().c_str());

    // initialize month name
    std::stringstream str_stream3;
    str_stream3 << std::put_time(localtime(&raw_time), "%B");
    month_name = str_stream3.str();


    // today's day of the week as a decimal (0-6)
    std::stringstream str_stream4;
    str_stream4 << std::put_time(localtime(&raw_time), "%w");
    int day_decimal = atoi(str_stream4.str().c_str());

    // get what day the first day of month was (i.e. jan:0, feb:1, etc)
    int firstPosition = get_first_day(day,day_decimal);

    // adds header lines to the list
    list.push_back("                    "+to_string(year));
    list.push_back("               "+month_name);
    list.push_back("   S    M    T    W    T     F    S");
    list.push_back("   --------------------------------------------");

    /// @author Fatima Hasan

    // adds extra space depending on first day of the month for the first line
    std::string spaces="   ";
    for (int i = 0; i < firstPosition; i++) {
        spaces+=("       ");
    }

    // gets number of days in a month
    int numOfDays = getNumOfDays(month,year);

    //adds days of the month to the list
    for (int j = 1; j <= numOfDays; j++) {
        if (j<10){
            spaces+=to_string(j)+"     ";
        }
        else{
            spaces+=to_string(j)+"   ";
        }
        if ((j + firstPosition) % WEEK == 0) {
            list.push_back(spaces);
            spaces="   ";
        }
    }

    list.push_back(spaces);

    firstPosition = (firstPosition + numOfDays - MIN_DAYS) % WEEK;
}

Calendar::~Calendar() {

}

/**
 * @author Fatima Hasan
 * @brief getNumOFDays method gets the number of days depending on the month and year
 * @param monthNumber : month number the user wants printed
 * @param year : year the user wants the month printed for
 * @return the number of days for a certain month
 */
int Calendar::getNumOfDays(int monthNumber, int year) {
    switch (monthNumber) {
        case 1: return 31;
        case 2: if (isLeapYear(year)) {
                return 29;
            } else {
                return 28;
            }
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
    }
}

/**
 * @author Fatima Hasan
 * @brief isLeapYear method checks to see if the chosen year is a leap year
 * @param year: chosen year by user
 * @return true if year is a Leap year and false otherwise
 */
bool Calendar::isLeapYear(int year) {
    if (year % 400 == 0){
        return true;
    }

    if (year % 100 == 0){
        return false;
    }

    return year % 4 == 0;
}


/**
 * @author Maryam Karimi
 * @brief this method returns the first day of the month as a decimal (0-6)
 * @param year: current year
 * @param today_week_num: today's day as a decimal num (0-6)
 */
int Calendar::get_first_day(int today, int today_week_num) {
    int result = today_week_num-(day%WEEK-1);
    if (result<0){
        result+=7;
    }
    return result;
}