
#ifndef GROUP6_TimeUI_h
#define GROUP6_TimeUI_h

#include "SDL/SDL.h"
#include "string"
#include "SDL/SDL_ttf.h"
#include "Time.h"
/***************************************************************************//**
* @class TimeUI
* @brief This class draws the time app onto the screen.
* @details This class takes the parameters the display the date and time on the spot specified by the loc parameter
* @author Jordan McInnis (jmcinni5@uwo.ca)
* @bug No know bugs.
*
******************************************************************************/
class TimeUI{
public:
    TimeUI(SDL_Surface*,int,int,int);
    void DrawTime();
    ~TimeUI();
private:
    SDL_Rect offset;
    TTF_Font *time_font;
    TTF_Font *date_font;
    int screenLocation;
    SDL_Surface* mainscreen;
    Time currentTime;
    SDL_Color textColor;
    SDL_Surface *time_surface;
    SDL_Surface *date_surface;
    SDL_Surface *clear;
    int region;
    int sizex;
    int sizey;
    SDL_Surface* clockbg;
};

#endif