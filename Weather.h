/**************************************************************************//**
* @file Weather.h
* @brief Contains the prototypes for the Weather class.
* @details This contains all the prototypes and global variables for the Weather class. 
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @bug No known bugs.
*
******************************************************************************/

#pragma once

class Weather {

    public:
        Weather(std::string city, std::string country);
        ~Weather();
        std::string getWeather();
    private:
        std::string ReadTheBuffer;

};