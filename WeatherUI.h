/**************************************************************************//**
* @file WeatherUI.h
* @brief Contains the prototypes for the WeatherUI class.
* @details This contains all the prototypes and global variables for the WeatherUI class. 
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @author Jordan McInnis (jmcinni5@uwo.ca)
* @bug No known bugs.
*
******************************************************************************/

#pragma once

class WeatherUI {

    public:
        WeatherUI(std::string, std::string, SDL_Surface*,int,int,int); 
        ~WeatherUI();
        void DrawWeather();
        bool isValid();
    private:
        SDL_Rect offset; 
        SDL_Surface* mainscreen;
        SDL_Color textColor;
        SDL_Surface *message;
        int screenLocation; 
        int sizex;
        int sizey;
        std::string temperature;
        std::string iconId;
        std::string Description;
        SDL_Surface* weatherbg;
        SDL_Surface *Conditions_surface;
        SDL_Surface *Temperature_surface;
        TTF_Font *Condition_font;
        TTF_Font *Tempurature_font;
        int region;
        bool Valid;

};
