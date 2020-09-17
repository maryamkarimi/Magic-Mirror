/******************************************************************************
*
* Name:	Jordan Mcinnis
* Email: 	jmcinni5@uwo.ca
*
*
******************************************************************************/

#ifndef GROUP6_UI_h
#define GROUP6_UI_h

#define USER_DIRECTORY  "Users"
#define REGISTERED   'r' ///< user_type for registered users
#define UNREGISTERED 'u' ///< user_type for unregistered users

#include "SDL/SDL.h"
#include "string"
#include <fstream>
#include "iostream"
#include "TimeUI.h"
#include "ReminderUI.h"
#include "WeatherUI.h"
#include "CalendarUI.h"
#include <fstream>
#include "Calendar.h"
#include "GreetingUI.h"
/******************************************************************************
*
* Name:	Jordan Mcinnis
* Email: 	jmcinni5@uwo.ca
*@brief UI.cpp is the main UI that manages all the back end of the project. UI.cpp manages the UI, it tells what apps go where, at what time
* for how long, handles user login , user preferences, user input, and houses the main
* 
*
******************************************************************************/
class UI{
private:
    int uCounter;
    SDL_Surface* mainscreen;
    SDL_Surface* freespot;
    SDL_Surface* clear;
    int freeSpots[4];
    int sizex,sizey;
    bool timeFlag;
    bool weatherFlag;
    std::string username;
    std::string username_no_txt;
    std::string password;
    std::string line;
    std::string user[6];
    std::string password1;
    void StartApps(std::string,std::string,std::string,std::string,bool,std::string);
    void StartTime(int);
    void StartCalender(int);
    void StartReminder(int);
    int GtimeLoc;
    int GweatherLoc;
    bool weatherStart;
    std::string input;
    std::string input2;

public:
    void StartWeather(int);
    UI(int,int);
    ~UI();
    int display(char);
    std::string wherePlace();
    SDL_Surface* getSurface();
    int Setup();
    bool UpdateUI(SDL_Event);
};

#endif