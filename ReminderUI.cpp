/******************************************************************************
*
* @author 	Maryam Karimi
* @email 	mkarimif@uwo.ca
*
* @brief ReminderUI.cpp is the user interface class for Reminder.
* It displays the reminders on the screen based on user's preferences
******************************************************************************/

#include "ReminderUI.h"

/******************************************************************************
* @brief the constructor for this class. it initializes the attributes for this class
* @param main: the main SDL_Surface from UI.cpp
* @param sizex: width of the screen
* @param sizey: height of the screen
* @param loc: an integer from 0-3 corresponding to the corner that the user wants the reminder to be displayed
* @param username: username associated with a smart mirror user
******************************************************************************/

ReminderUI::ReminderUI(SDL_Surface* main, int sizex, int sizey,int loc,std::string username){
    this->sizex = sizex;
    this->sizey = sizey;
    this->username = username;
    this->mainscreen = main;
    this->region = loc;
    this->textColor = { 255, 255, 255 };
    this->clear = SDL_LoadBMP("BMPs/ClearAv.bmp");
    this->reminders_font = TTF_OpenFont( FONT, 20 );
    TTF_Init();
}

/******************************************************************************
* @brief ReminderUI destructor
******************************************************************************/
ReminderUI::~ReminderUI(){
}

/******************************************************************************
* @brief this method displays the reminders on the chosen region
******************************************************************************/
void ReminderUI::DrawReminder(){

    // make an obj of Reminder with username and get the list of today's reminders for this user, as well as an iterator of the list
    Reminder reminder(username);
    std::list<std::string> list = reminder.get_reminder_list();
    std::list<std::string>::const_iterator it = list.begin();

    // num_lines counts the number of lines that the reminders need to be displayed on the screen properly
    // this number is then multiplied by a constant to find the required space for all of the reminders
    int num_lines = 1;
    for (it; it!=list.end();it++) {
        std::string reminder = *it;
        // divides the length of current reminder by NUM_CHARS (max number of chars in one line) to see how many lines are needed
        num_lines+=(reminder.length()/NUM_CHARS)+1;
    }

    // update the offset based on region and num_lines
    update_offset(region,num_lines);

    // resets the values of list and it by calling get_reminder_list again
    list = reminder.get_reminder_list();
    it = list.begin();

    // the surface that the reminders will be displayed on
    SDL_Surface *cur_surface = NULL;

    SDL_BlitSurface( clear, NULL, mainscreen, &offset);

    // for every reminder to be displayed:
    for (it; it!=list.end();it++){

        std::string reminder = *it;

        // if the length of this reminder is smaller than NUM_CHARS, display all of it on one line
        if (reminder.length()<=NUM_CHARS) {
            cur_surface = TTF_RenderText_Solid(reminders_font, reminder.c_str(), textColor);
            SDL_BlitSurface(cur_surface, NULL, mainscreen, &offset);
            if (offset.y > (sizey / 2)) {
                offset.y = offset.y - 20;
            }
            else {
                offset.y = offset.y + 40;
            }
        }

        // if the length of this reminder is greater than NUM_CHARS
        else{
            char line[reminder.length()];
            strcpy(line,reminder.c_str());

            // breaks the reminder to reminder.length()/NUM_CHARS)+1 lines
            for (int i=0; i<(reminder.length()/NUM_CHARS)+1; i++){
                char cur_line[NUM_CHARS+2];

                if (i>0){
                    cur_line[0]='-';
                    memmove(cur_line+1,line+(NUM_CHARS*i),NUM_CHARS);
                    cur_line[NUM_CHARS+1]='\0';
                }
                else{
                    memmove(cur_line,line+(NUM_CHARS*i),NUM_CHARS);
                    cur_line[NUM_CHARS]='\0';
                }

                cur_surface = TTF_RenderText_Solid(reminders_font, cur_line, textColor);
                SDL_BlitSurface(cur_surface, NULL, mainscreen, &offset);
                offset.y = offset.y + 20;
            }

            offset.y = offset.y + 20;

        }
    }

    SDL_Flip( mainscreen);

}


/******************************************************************************
* @authors Jordan Mcinnis, Maryam Karimi
* @emails jmcinni5@uwo.ca, mkarimif@uwo.ca
* @brief this method updates the x and y offsets based on region and num_lines
* so that the reminders are displayed on the proper coordinates
* @parameter region: loc: an integer from 0-3 corresponding to the corner that the user wants the reminder to be displayed
* @parameter num_lines: number of lines to be shown on the screen (max length of NUM_CHARS characters)
******************************************************************************/
void ReminderUI::update_offset(int region,int num_lines){

    // change the offset based on the region. num_lines is used for bottom right and bottom left
    if(region == 0){ //top left

        offset.x = 0;
        offset.y = 0;
    }

    if(region == 1){ //bottom left

        offset.x = 0;
        offset.y = sizey - num_lines*20;
    }

    if(region == 2){ //bottom right

        offset.x = sizex -340;
        offset.y = sizey - num_lines*20;
    }

    if(region == 3){ //top right

        offset.x = sizex -340;
        offset.y = 0;
    }
}