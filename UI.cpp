/******************************************************************************
*
* Name:	Jordan Mcinnis
* Email: 	jmcinni5@uwo.ca
*
*
******************************************************************************/

#include "UI.h"

/*@brief Initializes the SDL screen and global varriables. Constructs the SDL screen and specifies the screenmode, starting
boolean values and declares all varriables on the screen to be free.
*/
UI::UI(int x,int y){
    uCounter = 0;
    sizex = x;
    sizey = y;
    mainscreen = NULL;
    freeSpots[0] = 0; ///<Upon startup all corners of the screen are free and ready to place an app test change for git
    freeSpots[1] = 1;
    freeSpots[2] = 2;
    freeSpots[3] = 3;
    weatherStart = false;
    SDL_Init( SDL_INIT_EVERYTHING );
    mainscreen = SDL_SetVideoMode( sizex, sizey, 32, SDL_SWSURFACE );

    SDL_WM_SetCaption( "Smart Mirror 0.4", NULL );
}
/*
*@brief Deconstructor. It Deconstructs stuff.
*/
UI::~UI(){
}
/*
*@brief Starts the clock. Starts the clock at the specified corner of the screen.
  @param loc defines the location of the screen the app will be plcaed at
  @return Void.
*/
void UI::StartTime(int loc){
    TimeUI timeApp(mainscreen,sizex,sizey,loc);
    timeApp.DrawTime();
}
/*
*@brief Starts the weather app. Starts the weather app at the specified corner of the screen and gets the required user
    input so we can check weather in a specific region.
  @param loc defines the location of the screen the app will be placed at
  @return Void.
*/
void UI::StartWeather(int loc){
    GETNEWINFO:std::cout << "Please enter the country you would like to view weather in.\n";
    std::cin >> input;
    std::cout << "Please enter the city you would like to view the weather in.\n";
    std::cin >> input2;
    WeatherUI weatherApp(input2,input,mainscreen,sizex,sizey,loc);

    if (weatherApp.isValid() == false) { ///< Error checking to see if the city on country are valid or not.
        std::cout << "Error city can't be found, please check your spelling or enter a different city." << std::endl; ///< Since the city was not recognized by the API print an error.
        goto GETNEWINFO; ///< And then go back to asking the user for new information.
    }
    weatherApp.DrawWeather();


}
/*
*@brief Starts the Calender app. Starts the calender app at the specified corner of the screen.
  @param loc defines the location of the screen the app will be placed at
  @return Void.
*/
void UI::StartCalender(int loc){
    CalendarUI calendarApp(mainscreen,sizex,sizey,loc);
    calendarApp.DrawCalendar();
}
/*
*@brief Starts the reminder app. Starts the reminder app at the specified corner of the screen.
  @param loc defines the location of the screen the app will be placed at
  @return Void.
*/
void UI::StartReminder(int loc){
    ReminderUI reminderApp(mainscreen,sizex,sizey,loc,username_no_txt);
    reminderApp.DrawReminder();
}
/*
*@brief Updates the UI. Updates the UI by redrawing all apps that need to be updated.
  @return Void.
*/
bool UI::UpdateUI(SDL_Event event){

    SDL_WaitEvent(&event);
    if (event.type == SDL_QUIT){
        return true;
    }
    uCounter =+1;
    StartTime(GtimeLoc);
    if (uCounter > 900){ ///<900s = 15min update time
        StartWeather(GweatherLoc);
        uCounter = 0;
    }

    return false;
}

/*
UI::Setup will create a file for each user, the file currently countains 6 lines, their password, the colour they
want, and the location preferences of all the apps. If file does not
exist that means the user is a new user and a new file will be created for the user.

/*
*@brief Setups the UI and apps for the first time. Setup will create a file for each user, the file countains 6 lines, their password, and the location preferences of all the apps. If file does not
exist that means the user is a new user and a new file will be created for the user.
  @return int.
*/
int UI::Setup(){
    std::cout << "Please Enter your username, if a new user, please Enter the username you would like to use: ";
    std::cin >> username;
    if (username == "guest"){
        GreetingUI greeting(mainscreen,sizex,sizey,"",UNREGISTERED);
        greeting.display_message();
        username_no_txt = "guest";
        StartApps("0","1","2","3",true,"guest");
        return 0;
    }
    username_no_txt = username;
    username = "./";
    username.append(USER_DIRECTORY);
    username.append("/");
    username.append(username_no_txt);
    username.append(".txt");

    std::ifstream userFile (username); ///<open the file and get the password
    if (userFile.is_open()){
        int i = 0;
        while ( getline (userFile,line) ){
            user[i] = line;
            i++;
        }
        userFile.close();

        retry:
        std::cout << "Please Enter your password: \n";
        std::cin >> password;
        if (password == user[0]){ ///<is the password right?
            GreetingUI greeting(mainscreen,sizex,sizey,username_no_txt,REGISTERED);
            greeting.display_message();
            StartApps(user[2],user[3],user[4],user[5],false,username); ///<Start the apps with the users Preferences
        }
        else{ ///<password is wrong
            std::cout << "Incorrect Password, try again\n";
            goto retry;
        }
    }
    else{ ///<new user
        std::ofstream newUserFile(username); ///<No need to close the file as the ofstream deconstructur handles that
        std::cout << "Please choose a password: \n";
        std::cin >> password;
        newUserFile << password;
        newUserFile.close();
        StartApps("","","","",false,username);
    }
    return 0;
}
/*
*@brief gets the screen. Gets the screen.
  @return SDL_Surface that is the main screen.
*/
SDL_Surface*  UI::getSurface(){
    return mainscreen;
}

/*
*@brief Starts the apps in the proper locations. Start Apps will start the smart mirror with the provided locations of all the apps, this prevents the user from
having to go through setup after every single log-in and fulfills the customizable usercase 1; This will pass the
locations gathered, or not gathered, in the setup function and display the appropriate apps in the appropriate
places.
  @param timeLoc location of the time app
  @param weatherloc location of the weather app
  @param calenderloc location of the calender app
  @param reminderloc location of the reminder app
  @param isGuest are we running the apps as a guest user
  @param user what is the user that is running the app
  @return Void.
*/
void UI::StartApps(std::string timeLoc,std::string weatherLoc ,std::string calenderLoc ,std::string reminderLoc ,bool isGuest, std::string user){
    bool updateflag = false;
    bool dTime,dCalender,dReminder,dWeather = false;

    std::string temp[6]; ///<countainer for holding user preferences
    std::cout<< "To not display an app at anytime press'H' and the app will not be drawn to any corner.\n";
    if(timeLoc == ""){
        std::cout << "Where would you like the time to be?\n";
        temp[2] = wherePlace();
        if (temp[2] != "22"){
            timeLoc = temp[2];
            updateflag = true;
            dTime = true;

        }
    }
    if(weatherLoc == ""){
        std::cout << "Where would you like the weather to be?\n";
        temp[3] = wherePlace();
        if (temp[3] != "22"){
            weatherLoc = temp[3];
            updateflag = true;
            dWeather = true;

        }

    }
    if(calenderLoc == ""){
        std::cout << "Where would you like the calender to be?\n";
        temp[4] = wherePlace();
        if (temp[4]!= "22"){
            calenderLoc = temp[4];
            updateflag = true;
            dCalender = true;


        }
    }
    if(reminderLoc == ""){
        std::cout << "Where would you like the reminders to be?\n";
        temp[5] = wherePlace();
        if(temp[5] != "22"){
            updateflag = true;
            dReminder = true;
            reminderLoc = temp[5];

        }
    }

    ///<These next 8 lines are here to save the users password and preferences from being overwritten
    if (updateflag == true){ ///<Do we need to update the user preferences file?
        std::string line;
        std::ifstream userFileIn(username); ///<declare input stream for saving first 2 lines
        getline (userFileIn,line);
        temp[0] = line;
        temp[1] = "red"; ///<pass
        userFileIn.close();

        std::ofstream UserFileOut(username); ///<declare output stream and write preferences
        for(int i = 0; i < 6; i++){
            UserFileOut << temp[i];
            UserFileOut << std::endl;
        }
    }

    if (reminderLoc != "" && weatherLoc!="" && calenderLoc !="" && timeLoc!=""){
        dTime = true;
        dWeather = true;
        dCalender = true;
        dReminder = true;
    }

    if(dTime == true){
        GtimeLoc = std::stoi(timeLoc);
        StartTime(GtimeLoc);
    }
    if(dWeather == true){
        if (weatherLoc == "0"){
            GweatherLoc = 0;
        }
        else if (weatherLoc == "1"){
            GweatherLoc = 1;
        }
        else if (weatherLoc == "2"){
            GweatherLoc = 2;
        }
        else {
            GweatherLoc = 3;
        }
        StartWeather(GweatherLoc);
    }
    if(dCalender == true){
        StartCalender(std::stoi(calenderLoc));
    }
    if(dReminder == true){
        StartReminder(std::stoi(reminderLoc));
    }
}
/*
*@brief Gets a valid placement of an app. Confirms what corners of the screen are free of apps and will get user input
    for one of these open locations
  @return std::string is the open spot for an app that is retrieved
*/
std::string UI::wherePlace(){
    freespot = NULL;
    clear = NULL;
    freespot = SDL_LoadBMP( "BMPs/Available.bmp" );
    clear = SDL_LoadBMP("BMPs/ClearAv.bmp");
    SDL_Rect offset;
    SDL_Surface *message = NULL;
    TTF_Font *font = NULL;
    std::string input;

    SDL_Color textColor = { 255, 255, 255 };
    TTF_Init();
    font = TTF_OpenFont( "Fonts/font.ttf", 12 );

    for(int i = 0;i<4;i++){
        if (freeSpots[i]==0){ ///<top left
            SDL_BlitSurface( freespot, NULL, mainscreen, NULL );
            message = TTF_RenderText_Solid( font, "Press 0", textColor );
            offset.x = 25;
            offset.y = 15;
            SDL_BlitSurface( message, NULL, mainscreen, &offset );
        }
        if (freeSpots[i]==1){ ///< bottum left

            offset.x = 0;
            offset.y = sizey-50;
            SDL_BlitSurface( freespot, NULL, mainscreen, &offset );
            message = TTF_RenderText_Solid( font, "Press 1", textColor );
            offset.x = offset.x + 25;
            offset.y = offset.y + 15;
            SDL_BlitSurface( message, NULL, mainscreen, &offset );
        }
        if (freeSpots[i]==2){ ///< buttom right

            offset.x = sizex-100;
            offset.y = sizey-50;
            SDL_BlitSurface( freespot, NULL, mainscreen, &offset );
            message = TTF_RenderText_Solid( font, "Press 2", textColor );
            offset.x = offset.x + 25;
            offset.y = offset.y + 15;
            SDL_BlitSurface( message, NULL, mainscreen, &offset );
        }
        if (freeSpots[i]==3){ ///< top right

            offset.x = sizex-100;
            offset.y = 0;
            SDL_BlitSurface( freespot, NULL, mainscreen, &offset );
            message = TTF_RenderText_Solid( font, "Press 3", textColor );
            offset.x = offset.x + 25;
            offset.y = offset.y + 15;
            SDL_BlitSurface( message, NULL, mainscreen, &offset );
        }
        SDL_Flip(mainscreen);

    }

    bool flag = false;
    std::cin >> input;

    ///<Error checking for input.
    while (true) {
        if (input == "0" || input == "1" || input == "2" || input == "3" || input == "H" ) {
            break;
        }
        std::cout << "Error: Please enter a 0, 1, 2, or 3 or H to hide the app" << std::endl;
        std::cin >> input;
    }

    ///<removing green boxes
    for (int i = 0; i < 4; i++){
        if (freeSpots[i]==0){ ///<top left
            SDL_BlitSurface( clear, NULL, mainscreen, NULL );
        }
        if (freeSpots[i]==1){ ///<bottom left
            offset.x = 0;
            offset.y = sizey-50;
            SDL_BlitSurface( clear, NULL, mainscreen, &offset );
        }
        if (freeSpots[i]==2){ ///<bottom right
            offset.x = sizex-100;
            offset.y = sizey-50;
            SDL_BlitSurface( clear, NULL, mainscreen, &offset );
        }
        if (freeSpots[i]==3){ ///<top right
            offset.x = sizex-100;
            offset.y = 0;
            SDL_BlitSurface( clear, NULL, mainscreen, &offset );
        }
        SDL_Flip(mainscreen);

    }

    if(input != "H"){
        for ( int i = 0; i < 4; i++){
            if(freeSpots[i] == std::stoi(input)){
                freeSpots[i] = 22; ///<can't put null here so for all intensive purposes 22 equals NULL
            }
        }
    }

    if(input == "0"){
        return "0";
    }
    if(input == "1"){
        return "1";
    }
    if(input == "2"){
        return "2";
    }
    if(input == "3"){
        return "3";
    }
    if(input == "H"){
        return "22"; ///<see line 346 about NULL reference
    }
}

int main( int argc, char* args[] )
{
    int secondCounter = 0;
    UI mainUI(800,800);

    mainUI.Setup(); ///<setup the mirror

    SDL_Event event;
    bool exit = false;

    while (exit == false){
        SDL_Delay(1000);
        SDL_WaitEvent(&event);
        exit = mainUI.UpdateUI(event);
        if (event.type == SDL_QUIT){
            exit = true;
        }
    }

}



