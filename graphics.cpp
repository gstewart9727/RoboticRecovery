// Filename     : graphics.cpp
// Version      : 0.0.1
// Version Date : 02/19/2019
// Programmer   : Gabriel Stewart
// Description  : This file contains the source for the menu traversal of the Robotic Recovery application


#include "graphics.h"

extern detectNet::Detection* detections;
extern int numDetections;
extern detectNet* net;

// Function     : mainMenu
// Description  : This function presents the user with menu option and allows them to select
// Parameters   : None
// Returns      : None
void mainMenu() {

    // Variable declaration
    int option;

    // Allow user to select option, then act based on selection
    bool quit = false;
    while (quit == false) {

        // Display main menu
        mainGraphic();

        // Collect user menu choice and call corresponding function
        std::cin >> option;

        // Verify number was entered
        while (!std::cin.good())
        {
            std::cin.clear();
        }

        // Call function corresponding to menu choice
        switch (option) {
            case 1:
                break;
            case 2:
                quit = true;
                break;
            default:
                break;
        }
    }
}


// Function     : usage
// Description  : This function displays usage information when help flag is specified
// Parameters   : None
// Returns      : None
void usage() {

    // Display usage information
    titleBar();

}


// Function     : recovery
// Description  : This function displays objects detected by camera for recovery
// Parameters   : None
// Returns      : None
void recovery() {

    // Display titlebar
    titleBar();

    // List items visible to camera
    for (int x = 0; x < numDetections; x++) {
        printf("\t   [x] %s\n", net->GetClassDesc(detections[x].ClassID));
    }

}


// Function     : mainGraphic
// Description  : This function displays the main menu graphic,
// Parameters   : None
// Returns      : None
void mainGraphic() {

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // Display contents
    titleBar();
    printf(" \t\tWelcome to the Robotic Recovery application!.\n This tool allows "
        "for the easy location and recovery of objects in the active zone\n\n");
    printf("\t  Please choose from one of the following options:\n");
    printf("\t   [1] Start Recovery\n");
    printf("\t   [2] Quit\n");
    printf("\t  Select Option: ");
}


// Function     : titleBar
// Description  : This function displays the titlebar
// Parameters   : None
// Returns      : None
void titleBar() {

    // Adjust size of terminal window
    system("printf '\e[8;30;83t'");

    printf("  ________________________________________________________________________________\n");
    printf(" |                                                                                |\n");
    printf(" |   ██████╗  ██████╗ ██████╗  ██████╗ ████████╗██╗ ██████╗                       |\n");
    printf(" |   ██╔══██╗██╔═══██╗██╔══██╗██╔═══██╗╚══██╔══╝██║██╔════╝                       |\n");
    printf(" |   ██████╔╝██║   ██║██████╔╝██║   ██║   ██║   ██║██║                            |\n");
    printf(" |   ██╔══██╗██║   ██║██╔══██╗██║   ██║   ██║   ██║██║                            |\n");
    printf(" |   ██║  ██║╚██████╔╝██████╔╝╚██████╔╝   ██║   ██║╚██████╗                       |\n");
    printf(" |   ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝    ╚═╝   ╚═╝ ╚═════╝                       |\n");
    printf(" |         ██████╗ ███████╗ ██████╗ ██████╗ ██╗   ██╗███████╗██████╗ ██╗   ██╗    |\n");
    printf(" |         ██╔══██╗██╔════╝██╔════╝██╔═══██╗██║   ██║██╔════╝██╔══██╗╚██╗ ██╔╝    |\n");
    printf(" |         ██████╔╝█████╗  ██║     ██║   ██║██║   ██║█████╗  ██████╔╝ ╚████╔╝     |\n");
    printf(" |         ██╔══██╗██╔══╝  ██║     ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗  ╚██╔╝      |\n");
    printf(" |         ██║  ██║███████╗╚██████╗╚██████╔╝ ╚████╔╝ ███████╗██║  ██║   ██║       |\n");
    printf(" |         ╚═╝  ╚═╝╚══════╝ ╚═════╝ ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝   ╚═╝       |\n");
    printf(" |________________________________________________________________________________|\n");                                                               
}