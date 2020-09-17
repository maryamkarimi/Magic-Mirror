/***************************************************************************//**
* @file WeatherUI.cpp
* @class WeatherUI
* @brief This class draws the weather UI onto the screen.
* @details This class takes the parameters for the city in the country you want to display the weathe, as well as the x & y details for this app and the location where on the screen this app should be.
* The class take the weather location information passed to it and sends it to the WeatherParser class.
* Then retrieves the temperature, icon id, and the weather discription and stores the values in relivent variables.
* When the method DrawWeather() is called, it will draw the weather information onto the screen in the location that was set when this class was initialized.
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @author Jordan McInnis (jmcinni5@uwo.ca)
* @bug No know bugs.
*
******************************************************************************/

// Includes
#include <iostream>
#include <algorithm>
#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "WeatherParser.h" ///< @header WeatherParser.h
#include "WeatherUI.h"  ///< @header WeatherUI.h

/**
 * @brief WeatherUI constructor.
 * @details The constructor for the WeatherUI class. Sets up all the variables for the WeatherUI class. Retrieves the weather data from the WeatherParser class.
 * @param country The country where the city is in.
 * @param city The city you want to display the weather for.
 * @param main The SDL Surface where the weather app will be displayed.
 * @param sizexin The X size of the screen to be displayed on.
 * @param sizeyin The Y size of the screen to be displayed on.
 * @param loc The location where the weather app will be displayed.
 */
WeatherUI::WeatherUI(std::string city, std::string country, SDL_Surface* main, int sizexin, int sizeyin, int loc) {

    /// Sets up the variables used for the location of the weather app.
    region = loc;
    sizex = sizexin;
    sizey = sizeyin;
    mainscreen = main;

    /// Calls the WeatherParser class.
    WeatherParser Weather(city, country);
    temperature = Weather.getTemperature(); ///< Gets the current temperature.
    temperature = temperature + " C";
    iconId = "WeatherIcons/";
    iconId = iconId + Weather.getIconId(); ///< Gets the IconId.
    iconId = iconId + ".bmp";
    Description = Weather.getDescription(); ///< Gets the description of the current weather.
    Valid = Weather.isFound(); ///< Checks to see if the city has been found or not.

    /// Sets the surfaces and fonts to NULL
    Condition_font = NULL;
    Tempurature_font = NULL;
    weatherbg = NULL;
    Conditions_surface = NULL;
    Temperature_surface = NULL;

    /// Sets up the fonts that will be used to display the weather information.
    TTF_Init();
    Condition_font = TTF_OpenFont( "Fonts/font.ttf", 30 );
    Tempurature_font = TTF_OpenFont( "Fonts/font.ttf", 30 );
    SDL_Color textColor = { 255, 255, 255 };
}

/**
 * @brief WeatherUI destructor.
 * @details The destructor for the WeatherUI class.
 */
WeatherUI::~WeatherUI(){

}


/**
 * @brief Draws the weather app on the screen.
 * @details Sets the x and y offsets for the app so it displays in the right location.
 * Then starts with drawing the weather discription onto screen, then changes the x & y offsets so the temperature doesn't overlap anything on the screen.
 * Draws the temperature on the screen then changes the x & y offsets so the weather icon doesn't overlap anything on the screen.
 * Draws the weather icon onto the screen then refreshes the screen.
 */
void WeatherUI::DrawWeather(){

    SDL_Surface* clear = SDL_LoadBMP("BMPs/ClearAv.bmp");

    int length = Description.length();

    if(region == 0){ ///< Top left of the screen.
        offset.x = 0;
        offset.y = 0;
    }
    if(region == 1){ ///< Bottum left of the screen.
        offset.x = 0;
        offset.y = sizey - 50;
    }
    if(region == 2){ /// Bottum right of the screen.
        offset.x = sizex- 14.5*length;
        offset.y = sizey - 50;
    }
    if(region == 3){ /// Top right of the screen.
        offset.x = sizex - 14.5*length;
        offset.y = 0;
    }

    /// Error checking for the weather discripion.
    if (Description.c_str() == NULL) {
        perror(Description.c_str());
    }
    if (temperature.c_str() == NULL) { ///<  If the temperature is null print an error.
        perror(temperature.c_str());
    }
    if (iconId.c_str() == NULL) { ///< If the icon id is null print an error.
        perror(iconId.c_str());
    }


    const char *CurrentTemperature = temperature.c_str();
    const char *CurrentConditions = Description.c_str(); ///< Convert to be used for render text.

    /// Loads the weather icon using the iconid.
    weatherbg = SDL_LoadBMP(iconId.c_str());

    SDL_BlitSurface( clear, NULL, mainscreen, &offset);
    Conditions_surface = TTF_RenderText_Solid(Condition_font, CurrentConditions, textColor);
    SDL_BlitSurface(Conditions_surface, NULL, mainscreen, &offset); ///< Loads the conditions onto the screen.

    /// Changes the x and y offsets so the temperature doesn't overlap with anything else on the screen.
    if(offset.y >  (sizey/2)){
        offset.y = offset.y - 40;
    }
    else{
        offset.y = offset.y + 40;
    }

    Temperature_surface = TTF_RenderText_Solid(Tempurature_font, CurrentTemperature, textColor); ///< Loads the temperature onto the screen.


    SDL_BlitSurface( Temperature_surface, NULL, mainscreen, &offset);

    /// Changes the x and y offsets so the weather icon doesn't overlap with anything else on the screen.
    if(offset.y >  (sizey/2)){
        offset.y = offset.y - 40;
    }
    else{
        offset.y = offset.y + 40;
    }
    Uint32 colorkey = SDL_MapRGB( weatherbg->format, 0xFF, 0xFF, 0xFF );
    SDL_SetColorKey( weatherbg, SDL_SRCCOLORKEY, colorkey );
    SDL_BlitSurface( weatherbg, NULL, mainscreen, &offset); ///< Loads the weather icon onto the screen.

    SDL_Flip(mainscreen); ///< Refreshes the screen.

}

/**
 * @brief Returns the boolean Valid.
 * @details Returns the boolean saying if the city is valid or not.
 * @return The boolean Valid.
 */
bool WeatherUI::isValid() {
    return Valid;
}
