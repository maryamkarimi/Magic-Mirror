/******************************************************************************
*
* Name: 	Jordan Mcinnis / Maryam Karimi
* Email: 	jmcinni5@uwo.ca / mkarimif@uwo.ca
*
*
******************************************************************************/

#ifndef GROUP6_REMINDERUI_H
#define GROUP6_REMINDERUI_H

#define NUM_CHARS   36 // max number of characters in one line for reminders
#define FONT "Fonts/font.ttf"

#include "Reminder.h"
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class ReminderUI{

public:
    ReminderUI(SDL_Surface*,int,int,int,std::string);
    ~ReminderUI();
    void DrawReminder();

private:
    std::string username;
    SDL_Rect offset;
    TTF_Font *reminders_font;
    int screenLocation;
    SDL_Surface* mainscreen;
    SDL_Color textColor;
    SDL_Surface *clear;
    int region;
    int sizex;
    int sizey;
    void update_offset(int,int);
};

#endif //GROUP6_REMINDERUI_H
