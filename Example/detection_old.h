// Filename     : detection.h
// Version      : 0.0.1
// Version Date : 02/25/2020
// Programmer   : Gabriel Stewart
// Description  : This file contains the header information for the detection class

#ifndef DETECTION_H
#define DETECTION_H

#include "global.h"
#include "gstCamera.h"
#include "glDisplay.h"

#include "detectNet.h"
#include "commandLine.h"

#include <signal.h>

using namespace std;

class Detection {
    public:
        // Create method for accessing instance of class
        static Detection* getInstance(int argc, char** argv);

        // Declare getters/setters

    protected:
        gstCamera* camera;
        detectNet* net;
        glDisplay* display;
        float* imgRGBA;
        detectNet::Detection* detections;
        std::string cameraIndex;

    private:
        static Detection* instance;
        void LiveDetection(const uint32_t overlayFlags);
        Detection(int argc, char** argv);
        ~Detection();
};

#endif
