//
// Created by Urshita Nanda on 2018-11-29.
//
#ifndef GROUP6_CalendarUI_h
#define GROUP6_CalendarUI_h

#include "SDL/SDL.h"
#include "string"
#include "SDL/SDL_ttf.h"
#include "Calendar.h"

class CalendarUI{
public:
    CalendarUI(SDL_Surface*,int,int,int);
    void DrawCalendar();
    ~CalendarUI();

private:
    SDL_Rect offset;
    TTF_Font *calendar_font;
    int screenLocation;
    SDL_Surface* mainscreen;
    Calendar currentCalendar();
    SDL_Color textColor;
    SDL_Surface *calendar_surface;
    SDL_Surface *clear;
    int region;
    int sizex;
    int sizey;
    SDL_Surface* clockbg;
};

#endif