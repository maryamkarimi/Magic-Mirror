/******************************************************************************
*
* @author 	Maryam Karimi
* @email	mkarimif@uwo.ca
*
* @headerfile for GreetingUI.cpp
******************************************************************************/

#ifndef GROUP6_GREETING_H
#define GROUP6_GREETING_H

#define REGISTERED   'r' // user_type for registered users
#define UNREGISTERED 'u' // user_type for unregistered users
#define FONT "Fonts/font.ttf"

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include <string>

class GreetingUI{
public:
    GreetingUI(SDL_Surface*, int,int,std::string,char);
    ~GreetingUI();
    void display_message();
    std::string get_message();
private:
    char user_type; // either 'r' or 'u'
    std::string username;
    SDL_Rect offset;
    TTF_Font *greeting_font;
    SDL_Surface* mainscreen;
    SDL_Surface *greeting_surface;
    SDL_Color textColor;
    SDL_Surface *clear;
    int sizex;
    int sizey;
};

#endif //GROUP6_GREETING_H
