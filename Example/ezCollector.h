// Filename     : ezCollector.h
// Version      : 0.0.1
// Version Date : 10/30/2019
// Programmer   : Gabriel Stewart
// Description  : This file contains prototypes for the ezCollector.cpp file.

#ifndef EZ_COLLECTOR_H
#define EZ_COLLECTOR_H


// Include headers
#include "global.h"
#include "gstCamera.h"
#include "imageIO.h"
#include "stb_image_write.h"

// Include libraries
#include <librealsense2/rs.hpp>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>


// Prototypes
int createStructure(const char* labelArg, int intervalArg, const char* cameraArg);
void collectRGBImages();
int collectDEPTHImages();
void metadata_to_csv(const rs2::frame& frm, const std::string& filename);
void watchdog(int sig);
void changeClass();
void changeType();
void changeInterval();

// Class Declaration
class gstCamera;
class glDisplay;

// Capture Class
class CaptureWindow
{
public:

        // Capture & render next camera frame
	void Render();

        // Save the latest frame to disk
	bool Save( const char* filename, int quality=95 );

        // Camera streaming status
	bool IsStreaming() const;

        // Camera dimensions
	int GetCameraWidth() const;
        int GetCameraHeight() const;

        float* imgRGBA;

protected:

        // Classes for camera operation and file manipulation
	gstCamera* camera;
	glDisplay* display;
};

#endif


