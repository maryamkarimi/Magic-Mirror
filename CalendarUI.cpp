/**
 * @author Maryam Karimi
 * @email mkarimif@uwo.ca
 *
 * @brief this class creates a user interface for the calendar
 */
#include "CalendarUI.h"

/**
 * @brief this is the constructor for this class, it initializes the attributes for this class
 * @param main :the main SDL_Surface from UI.cpp
 * @param sizexin : the width of the screen
 * @param sizeyin : the height of the screen
 * @param loc : an integer from 0-3 corresponding to the corner that the user wants the reminder to be displayed
 */
CalendarUI::CalendarUI(SDL_Surface* main,int sizexin,int sizeyin,int loc){

    sizex = sizexin;
    sizey = sizeyin;

    mainscreen = main;
    region = loc;
    calendar_surface = NULL;

    calendar_font = NULL;
    textColor = { 255, 255, 255 };
    TTF_Init();
    clockbg = NULL;

    clear = SDL_LoadBMP("BMPs/ClearAv.bmp");
    calendar_font = TTF_OpenFont( "Fonts/font.ttf", 15 );

}

CalendarUI::~CalendarUI(){
}


/**
 * @brief this method displays the calendar on the chosen region
 */
void CalendarUI::DrawCalendar(){

    if(region == 0){ //top left

        offset.x = 0;
        offset.y = 0;
    }

    if(region == 1){ //bottom left

        offset.x = 0;
        offset.y = sizey - 220;
    }

    if(region == 2){ //bottom right

        offset.x = sizex -220;
        offset.y = sizey - 220;
    }

    if(region == 3){ //top right

        offset.x = sizex -340;
        offset.y = 0;
    }

    Calendar cal;
    std::list<std::string>::const_iterator it = cal.list.begin();

    // the surface that the reminders will be displayed on
    SDL_Surface *cur_surface = NULL;

    SDL_BlitSurface( clear, NULL, mainscreen, &offset);

    // for every reminder to be displayed:
    for (it; it!=cal.list.end();it++){

        std::string line = *it;

        cur_surface = TTF_RenderText_Solid(calendar_font, line.c_str(), textColor);
        SDL_BlitSurface(cur_surface, NULL, mainscreen, &offset);

        offset.y = offset.y + 20;
    }

    SDL_Flip( mainscreen);
}