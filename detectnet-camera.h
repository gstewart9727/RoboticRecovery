// Filename     : detection.h
// Version      : 0.0.1
// Version Date : 02/25/2020
// Programmer   : Gabriel Stewart
// Description  : This file contains the header information for the detection functions

#ifndef DETECTION_H
#define DETECTION_H

#include "global.h"
#include "gstCamera.h"
#include "glDisplay.h"
#include "detectNet.h"
#include "commandLine.h"

#include <signal.h>

using namespace std;

void sig_handler(int signo);
int detection_start(int argc, char** argv);

#endif
