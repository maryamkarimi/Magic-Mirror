/******************************************************************************
*
* Name:	Jordan Mcinnis
* Email: 	jmcinni5@uwo.ca
*
*
******************************************************************************/

#include "TimeUI.h"
/** 
 * @brief TimeUI constructor.
 * @details The constructor for the TimeUI class. Sets up all the variables for the TimeUI class, retrieves the time from the time.cpp class.
 * @param main The SDL Surface where the app will be displayed.
 * @param sizexin The X size of the screen to be displayed on.
 * @param sizeyin The Y size of the screen to be displayed on.
 * @param loc The location where the time app will be displayed.
 */
TimeUI::TimeUI(SDL_Surface* main,int sizexin,int sizeyin,int loc){
    
    sizex = sizexin;
    sizey = sizeyin;
    
    mainscreen = main;
    region = loc;
    time_surface = NULL;
    date_surface = NULL;
    
    time_font = NULL;
    date_font = NULL;
    textColor = { 0, 255, 0 };
    TTF_Init();
    clockbg = NULL;
   
    clear = SDL_LoadBMP("BMPs/ClearAv.bmp");
    time_font = TTF_OpenFont( "Fonts/font.ttf", 40 );
    date_font = TTF_OpenFont( "Fonts/font.ttf", 20 );
   
}
/*
*@brief Deconstructor. Deconstructor.
*/
TimeUI::~TimeUI(){
}
/*
*@brief Draws the time. Draws the time to the screen at the location specified by loc
  @return Void.
*/
void TimeUI::DrawTime(){
    
    std::string cur_time = currentTime.get_time();
    std::string cur_date = currentTime.get_date();
   
    if(region == 0){ ///<top left
        
        offset.x = 5;
        offset.y = 5;
    }
    if(region == 1){ ///<bottom left
     
        offset.x = 5;
        offset.y = sizey - 50;
    }
    if(region == 2){ ///<bottom right
        
        offset.x = sizex -175;
        offset.y = sizey - 50;
    }
    if(region == 3){ ///<top right
       
        offset.x = sizex -175;
        offset.y = 0;
    }
    
    time_surface = TTF_RenderText_Solid( time_font, cur_time.c_str(), textColor ); 
    date_surface = TTF_RenderText_Solid( date_font, cur_date.c_str(), textColor ); 
    SDL_BlitSurface( clear, NULL, mainscreen, &offset);
    SDL_BlitSurface( time_surface, NULL, mainscreen, &offset );
    if(offset.y >  (sizey/2)){
        offset.y = offset.y - 20;
    }
    else{
        offset.y = offset.y + 40;
    }
    SDL_BlitSurface( date_surface, NULL, mainscreen, &offset );
   
    SDL_Flip( mainscreen);
    
}

