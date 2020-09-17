/***************************************************************************//**
* @file Weather.cpp
* @class Weather
* @brief A class that retrieves current weather information from a weather API.
* @details This class takes the parameters for the city in the country you want to display the weather. 
* The class take the location passed to it and sends it to the weather API. 
* It then takes the json response from the API and puts it into a string.
* The string can be then retrieved using the getWeather() method.
* @author Gerrit Mulder (gmulder3@uwo.ca)
* @bug No know bugs.
*
******************************************************************************/

// Includes
#include <iostream>
#include <string>
#include <curl/curl.h>
#include "Weather.h" ///< @header Weather.h


/** 
 * @brief The callback function.
 * @details This callback function gets called by libcurl as soon as there is data received that needs to be saved.
 * For most transfers, this callback gets called many times and each invoke delivers another chunk of data.
 * @param contents Points to the delivered data.
 * @param size This is always 1.
 * @param nmemb This is the size of the delivered data.
 * @param userp This is an argument set with the CURLOPT_WRITEDATA option. In this case userp is the string ReadTheBuffer.
 * @return Returns the number of bytes taken care of.
 */
static size_t  WriteResponse(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb); ///< Writes the data recieved from the API into userp.
    return size * nmemb;
}

/** 
 * @brief The constructor for the Weather class.
 * @details This constructor using the location data passed to it, will call the weather API and store the response (data) it gets from the API in a string.
 * @param country The country where the city is in.
 * @param city The city you want to display the weather for.
 */
Weather::Weather(std::string city, std::string country) {

    /// Creates the CURL object used for interacting with the API.
    CURL *curl;
    CURLcode res;

    /// Initialize CURL.
    curl = curl_easy_init();

    /// If curl works then make the call to the API.
    if (curl) {

        /// Constructs the string of the API, inserting in the city and country.
        std::string URL = "http://api.openweathermap.org/data/2.5/weather?q=" + city + "," + country + "&units=metric&APPID=3e3a4aafb34316e4635212573be0078c";
        
        curl_easy_setopt(curl, CURLOPT_URL, URL.c_str()); ///< Sets the URL of the API CURL will call.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteResponse); ///< Sets the callback function for CURL.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ReadTheBuffer); ///< Sets up and tells CURL where to store the information it gets from the API.
        res = curl_easy_perform(curl); ///< Calls the API and gets a response.

        /// Check to see if getting information from the API worked or not.
        if (res != CURLE_OK) {
            fprintf(stderr, "Please check your internet connection\n", curl_easy_strerror(res));
            exit(EXIT_FAILURE);
        }

        /// Always cleanup.
        curl_easy_cleanup(curl);
    }


    else { ///< Curl didn't work so print an error.
        perror("Error: curl initiazation failed.");
        exit(EXIT_FAILURE);
    }

}


/** 
 * @brief Weather destructor.
 * @details The destructor for the Weather class.
 */
Weather::~Weather() {

}

/** 
 * @brief Returns the weather information. 
 * @details Returns a string with all the weather information gotten from the API.
 * @return All the weather information retrieved from the weather API in a string.
 */
std::string Weather::getWeather() {
    return ReadTheBuffer;
}