/***************************************************************************//**
* @file WeatherParser.cpp
* @class WeatherParser
* @brief A class that parses the weather data obtained from the Weather class.
* @details This class calls the Weather class and passes it the required location data.
* Then it retrieves the weather data from the Weather class and then starts parsing the weather data.
* It parses the data by putting it into a string stream and then tokenizing that string stream getting rid of un-needed charecters in the data.
* Then it puts the string stream into a vector and iterates through the vector looking for the required weather information and storing the found information into strings
* This information can be retrieved using the getTemperature(), getIconId(), or getDescription() methods.
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @bug No know bugs.
*
******************************************************************************/

// Includes
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <iterator>
#include "WeatherParser.h" ///< @header WeatherParser.h
#include "Weather.h" ///< @header Weather.h

/** 
 * @struct tokens
 * @brief Token structure.
 * @details Token structure, a structure that tells the string stream where to split at.
 */
struct tokens: std::ctype<char> {

    /** 
    * @brief The token constructor.
    * @details Calls the get_table() method.
    */
    tokens(): std::ctype<char>(get_table()) {
    }

    /** 
    * @brief Creates a delimiter for tokenizing.
    * @details Creates a delimiter to be used for tokenizing a vector. 
    * It does this by creating a mask (called delim) that turns all the charecters I want to tokenize at into spaces, and also turns all spaces into digits so it doesn't spilt there.
    * @return The delimiter
    */
    static std::ctype_base::mask const* get_table() {

        typedef std::ctype<char> cctype;
        static const cctype::mask *const_delim = cctype::classic_table();

        static cctype::mask delim[cctype::table_size];
        std::memcpy(delim, const_delim, cctype::table_size * sizeof(cctype::mask)); 

        /// The charecters that are to be split at.
        delim['{'] = std::ctype_base::space;
        delim['}'] = std::ctype_base::space;
        delim[':'] = std::ctype_base::space;
        delim['"'] = std::ctype_base::space;
        delim[','] = std::ctype_base::space;
        delim['['] = std::ctype_base::space;
        delim[']'] = std::ctype_base::space;
        delim[' '] = std::ctype_base::digit; ///< Changes spaces into digits so they aren't split at.

        return &delim[0];
    }
}; 

/** 
 * @brief The constructor for the WeatherParser class.
 * @details Using the location data passed to it, this constructor calls the Weather class and recieves the weather information from it putting the weather information into a vertor.
 * Then it iterates through the vector looking for the description, icon id, and the temperature.
 * @param country The country where the city is in.
 * @param city The city you want to display the weather for.
 */
WeatherParser::WeatherParser(std::string city, std::string country) {

    /// Calls the Weather class.
    Weather WeatherObj(city, country);
    std::string weather = WeatherObj.getWeather();
    std::stringstream ss(weather);
    ss.imbue(std::locale(std::locale(), new tokens())); ///< Tokenizes the string stream so it's just words and spaces.
    std::istream_iterator<std::string> begin(ss);
    std::istream_iterator<std::string> end;
    std::vector<std::string> WeatherVector(begin, end); ///< Fills the vector with all the weather data.

    /// Loops through weather vector and assigns values to the weather variables based on the current weather conditions. 
    for (std::vector<std::string>::const_iterator i = WeatherVector.begin(); i != WeatherVector.end(); ++i) {

        check = *i;

        if (check == "description") { ///< If check equals "description" then set the description variable to the next location of the pointer i.
            i++;
            description = *i;
        }
        else if (check == "icon") { ///< If check equals "icon" then set the icon variable to the next location of the pointer i.
            i++;
            descriptionIconId = *i;
        }
        else if (check == "temp") { ///< If check equals "temp" then set the temperature variable to the next location of the pointer i.
            i++;
            temperature = *i;
            break; ///< Since the temperature has been found break out of the loop as all the rest of the weather data is un-needed.
        }
        else if (check == "city not found"){ ///< If check equals "city not found" then the city the user entered is invalid or can't be found. So set the Found boolean to false and break out of the loop.
            std::cout << "not found" << std::endl;
            Found = false;
            break;
        }
    }
    
}

/** 
 * @brief The WeatherParser destructor.
 * @details The destructor for the WeatherParser class.
 */
WeatherParser::~WeatherParser() {

}

/** 
 * @brief Returns the temperature.
 * @details Returns the temperature in the form of a string.
 * @return The temperature.
 */
std::string WeatherParser::getTemperature() {
    return temperature;
}

/** 
 * @brief Returns the icon id.
 * @details Returns the Id of the icon assoiated with the current weather in a string.
 * @return The icon Id.
 */
std::string WeatherParser::getIconId() {
    return descriptionIconId;
}


/** 
 * @brief Returns the discription of the weather.
 * @details Returns the description of the current weather in a string.
 * @return The discription of the weather.
 */
std::string WeatherParser::getDescription() {
    return description;
}

/** 
 * @brief Returns the boolean Found.
 * @details Returns the boolean saying if the city is valid or not.
 * @return The boolean Found.
 */
bool WeatherParser::isFound(){
    return Found;
}