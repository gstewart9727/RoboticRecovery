// Filename     : main.cpp
// Version      : 0.0.1
// Version Date : 02/19/2019
// Programmer   : Gabriel Stewart
// Source       : https://github.com/dusty-nv/jetson-inference/tree/master/examples
// Description  : This file calls the Robotic Recovery application. The tool allows users to request the 
//                recovery of objects in the active zone through the use of a robotic arm.


// Includes
#include "global.h"


// Function     : main
// Description  : This function parses the command line and begins operation
// Parameters   : argc/argv - command line arguments
// Returns      : int - Indicating return status
int main(int argc, char** argv) {

    // Parse command line arguments
    commandLine cmdLine(argc, argv);

    // If help or the help flag are specified, present the usage of the application
    if( cmdLine.GetFlag("help") ) {
            usage();
            return 0;
    }

    // Start object detection
    std::thread t1(detection_start, argc, argv);

    // Begin menu loop
    std:: thread t2(mainMenu);

    t1.join();
    t2.join();

    return 0;
}

