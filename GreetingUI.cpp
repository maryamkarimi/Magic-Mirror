/******************************************************************************
*
* @author 	Maryam Karimi
* @email	mkarimif@uwo.ca
*
* @brief GreetingUI.cpp makes a personalized message for users or a general message
* for unregistered users (guest) and displays it on the screen
******************************************************************************/

#include "GreetingUI.h"
#include "iostream"

/******************************************************************************
* @brief constructor for this class: initializes username and user_type
* @param user_type : either 'r' for registered or 'u' for unregistered
******************************************************************************/
GreetingUI::GreetingUI(SDL_Surface* main, int sizex, int sizey,std::string username, char user_type){
    this->username = username;
    this->user_type = user_type;
    this->sizex = sizex;
    this->sizey = sizey;
    mainscreen = main;
    greeting_surface = NULL;
    greeting_font = NULL;
    textColor = { 255, 255, 255 };
    TTF_Init();
    clear = SDL_LoadBMP("BMPs/ClearAv.bmp");
    greeting_font = TTF_OpenFont( FONT, 30);
}

/******************************************************************************
* @brief GreetingUI destructor
******************************************************************************/
GreetingUI::~GreetingUI(){
}

/******************************************************************************
* @brief this class displays the message created by get_message on the screen
* for DISPLAY_TIME milliseconds
******************************************************************************/
void GreetingUI::display_message() {

    offset.x = sizex/3;
    offset.y = sizey/3 ;
    greeting_surface = TTF_RenderText_Solid( greeting_font, get_message().c_str(), textColor);
    SDL_BlitSurface( clear, NULL, mainscreen, &offset);
    SDL_BlitSurface( greeting_surface, NULL, mainscreen, &offset);

    SDL_Flip( mainscreen);
    SDL_Delay(3000);

    SDL_BlitSurface( clear, NULL, mainscreen, &offset);
    SDL_Flip( mainscreen);

}

/******************************************************************************
* @brief this class creates a greeting message for users
* @returns the greeting message to be displayed
******************************************************************************/
std::string GreetingUI::get_message(){

    std::string message;

    message= "Welcome ";

    if (user_type == REGISTERED){
        message = message + username;
    }

    return message+"\n";
}