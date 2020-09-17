/**************************************************************************//**
* @file WeatherParser.h
* @brief Contains the prototypes for the WeatherParser class.
* @details This contains all the prototypes and global variables for the WeatherParser class. 
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @bug No known bugs.
*
******************************************************************************/

#pragma once


class WeatherParser {

    public:
        WeatherParser(std::string city, std::string country);
        ~WeatherParser();
        void ParseWeather(std::string weather);
        std::string getIconId();
        std::string getDescription();
        std::string getTemperature();
        bool isFound();
    private:
        std::string description;
        std::string descriptionIconId;
        std::string temperature;
        std::string check;
        bool Found = true;
};