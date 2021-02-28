// Filename     : graphics.cpp
// Version      : 0.0.1
// Version Date : 10/30/2019
// Programmer   : Gabriel Stewart
// Description  : This file contains the source for the menu traversal of the ezCollector tool.


#include "graphics.h"


// Function     : mainMenu
// Description  : This function presents the user with menu option and allows them to select
// Parameters   : None
// Returns      : None
void mainMenu() {

    // Variable declaration
    int option;
    std::string path;

    // Allow user to select option, then act based on selection
    bool quit = false;
    while (quit == false) {

        // Display main menu
        mainGraphic(path);

        // Collect user menu choice and call corresponding function
        std::cin >> option;

        // Verify number was entered
        while (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }

        // Call function corresponding to menu choice
        switch (option) {
            case 1:
                changeClass();
                break;
            case 2:
                changeInterval();
                break;
            case 3:
                changeType();
                break;
            case 4:
                startCapture();
                break;
            case 5:
		break;
            case 6:
                quit = true;
                running = false;
                std::cout << "\x1b[2J\x1b[H";
                break;
            default:
                break;
        }
    }
}


// Function     : countFiles
// Description  : This function counts the number of files in the active directory
// Parameters   : None
// Returns      : None
int countFiles(std::string path) try {

    // Variable Declaration
    DIR *dp;
    int i = 0;
    struct dirent *ep;
    std::string dir = "./";

    // Open active directory
    dir += classNames[activeClass];
    dp = opendir (path.c_str());

    // Count files in directory
    if (dp != NULL)
    {
        while (ep = readdir (dp))
            i++;

        (void) closedir (dp);
    }
    else
        throw std::exception();

    // Image count is offset by 2
    return i - 2;
}
catch (std::exception e) {
    // If an exception is thrown, exit application
    std::exit(10);
}


// Function     : usage
// Description  : This function displays usage information when help flag is specified
// Parameters   : None
// Returns      : None
void usage() {

    // Display usage information
    titleBar();
    printf("\tUsage: ezCollector [--help] [--camera CAMERA] [--interval INTERVAL] [--labels LABELS]\n\n");
    printf("\tGather images at specified intervals and organize them into a dataset.\n\n");
    printf("\tArguments:\n");
    printf("\t  -help                 Show this help message and exit\n");
    printf("\t  -camera CAMERA        Index of the MIPI CSI camera to use (e.g. CSI camera 0),\n");
    printf("\t                        or for VL42 cameras, the /dev/video device to use.\n");
    printf("\t                        By default, /dev/video2 will be used.\n");
    printf("\t  -interval INTERVAL    Time (in seconds) delay between the capture of each image.\n");
    printf("\t                        By default, 5 seconds will be used.\n");
    printf("\t  -labels LABELS        REQUIRED - Location of the labels.txt file containing class names.\n");
    printf("\t                        Location should be absolute path.\n");
}


// Function     : mainGraphic
// Description  : This function displays the main menu graphic,
// Parameters   : None
// Returns      : None
void mainGraphic(std::string path) {

    path = cwd;
    path += "/";
    path += types[activeType];
    path += "/";
    path += classNames[activeClass];

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // Display contents
    titleBar();
    printf(" Welcome to the ez Collector tool. This tool will automate the collection of an  organized dataset.\n\n");
    printf("\t  \033[4mStatus\033[0m\n");
    printf("\t   Current Class: %s\n", classNames[activeClass]);
    printf("\t   Current Interval: %d\n", currentInterval.load());
    printf("\t   Image Type: %s\n", types[activeType]);
    printf("\t   Image Directory: \n\t   %s\n", path.c_str());
    printf("\t   Images Captured: %d\n", countFiles(path));
    if (running)
        printf("\t   Running: True\n\n");
    else
        printf("\t   Running: False\n\n");
    printf("\t  Please choose from one of the following options:\n");
    printf("\t   [1] Change active class\n");
    printf("\t   [2] Change capture interval\n");
    printf("\t   [3] Change image type\n");
    printf("\t   [4] Start/Stop capture\n");
    printf("\t   [5] Refresh Stats\n");
    printf("\t   [6] Quit\n\n");
    printf("\t  Select Option: ");
}


// Function     : titleBar
// Description  : This function displays the titlebar
// Parameters   : None
// Returns      : None
void titleBar() {

    // Adjust size of terminal window
    system("printf '\e[8;30;99t'");

    printf("  ________________________________________________________________________________________________\n");
    printf(" |                                                                                                |\n");
    printf(" | ███████╗███████╗     ██████╗ ██████╗ ██╗     ██╗     ███████╗ ██████╗████████╗ ██████╗ ██████╗ |\n");
    printf(" | ██╔════╝╚══███╔╝    ██╔════╝██╔═══██╗██║     ██║     ██╔════╝██╔════╝╚══██╔══╝██╔═══██╗██╔══██╗|\n");
    printf(" | █████╗    ███╔╝     ██║     ██║   ██║██║     ██║     █████╗  ██║        ██║   ██║   ██║██████╔╝|\n");
    printf(" | ██╔══╝   ███╔╝      ██║     ██║   ██║██║     ██║     ██╔══╝  ██║        ██║   ██║   ██║██╔══██╗|\n");
    printf(" | ███████╗███████╗    ╚██████╗╚██████╔╝███████╗███████╗███████╗╚██████╗   ██║   ╚██████╔╝██║  ██║|\n");
    printf(" | ╚══════╝╚══════╝     ╚═════╝ ╚═════╝ ╚══════╝╚══════╝╚══════╝ ╚═════╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝|\n");
    printf(" |________________________________________________________________________________________________|\n\n");
}
