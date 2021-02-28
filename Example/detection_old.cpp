// Filename     : detection.cpp
// Version      : 0.0.1
// Version Date : 02/25/2020
// Programmer   : Gabriel Stewart
// Description  : This file contains the source code for the detection class

#include "detection.h"


bool signal_recieved = false;

Detection* Detection::instance = NULL;

Detection* Detection::getInstance(int argc, char** argv) {
	if (instance == NULL) {
		instance = new Detection(argc, argv);
	}
	return(instance);
}

void sig_handler(int signo)
{
	if( signo == SIGINT )
	{
		printf("received SIGINT\n");
		signal_recieved = true;
	}
}

Detection::Detection(int argc, char** argv)
{
	commandLine cmdLine(argc, argv);

	// Attach interrupt signal handler
	if(signal(SIGINT, sig_handler) == SIG_ERR)
		printf("\ncan't catch SIGINT\n");


	// Create camera device
	camera = gstCamera::Create(cmdLine.GetInt("width", gstCamera::DefaultWidth),
								   cmdLine.GetInt("height", gstCamera::DefaultHeight),
								   cmdLine.GetString("camera"));

	if(!camera) {
		printf("\ndetectnet-camera:  failed to initialize camera device\n");
		return;
	}
	
	// Display results
	printf("\ndetectnet-camera:  successfully initialized camera device\n");
	printf("    width:  %u\n", camera->GetWidth());
	printf("   height:  %u\n", camera->GetHeight());
	printf("    depth:  %u (bpp)\n\n", camera->GetPixelDepth());

	// Create detection network
	net = detectNet::Create(argc, argv);

	if(!net) {
		printf("detectnet-camera:   failed to load detectNet model\n");
		return;
	}

	// Parse overlay flags
	const uint32_t overlayFlags = detectNet::OverlayFlagsFromStr(cmdLine.GetString("overlay", "box,labels,conf"));

	// Create display window
	display = glDisplay::Create();

	if(!display) {
		printf("detectnet-camera:  failed to create openGL display\n");
		return;
	}

	// Start camera stream
	if(!camera->Open()) {
		printf("detectnet-camera:  failed to open camera for streaming\n");
		return;
	}
	
	printf("detectnet-camera:  camera open for streaming\n");

	// Start object detection
	std::thread t1(&Detection::LiveDetection, this, overlayFlags);
	t1.detach();
}

Detection::~Detection()
{
	// Destroy Resources reserved by class
	printf("detectnet-camera:  shutting down...\n");
	
	SAFE_DELETE(camera);
	SAFE_DELETE(display);
	SAFE_DELETE(net);

	printf("detectnet-camera:  shutdown complete.\n");
}


void Detection::LiveDetection(const uint32_t overlayFlags) 
{
/*
	 * processing loop
	 */
	float confidence = 0.0f;
	
	while( !signal_recieved )
	{
		// capture RGBA image
		imgRGBA = NULL;
		
		if( !camera->CaptureRGBA(&imgRGBA, 1000) )
			printf("detectnet-camera:  failed to capture RGBA image from camera\n");

		// detect objects in the frame
		detections = NULL;
	
		const int numDetections = net->Detect(imgRGBA, camera->GetWidth(), camera->GetHeight(), &detections, overlayFlags);
		
		if( numDetections > 0 )
		{
			printf("%i objects detected\n", numDetections);
		
			for( int n=0; n < numDetections; n++ )
			{
				printf("detected obj %i  class #%u (%s)  confidence=%f\n", n, detections[n].ClassID, net->GetClassDesc(detections[n].ClassID), detections[n].Confidence);
				printf("bounding box %i  (%f, %f)  (%f, %f)  w=%f  h=%f\n", n, detections[n].Left, detections[n].Top, detections[n].Right, detections[n].Bottom, detections[n].Width(), detections[n].Height()); 
			}
		}	

		// update display
		if( display != NULL )
		{
			// render the image
			display->RenderOnce(imgRGBA, camera->GetWidth(), camera->GetHeight());

			// update the status bar
			char str[256];
			sprintf(str, "TensorRT %i.%i.%i | %s | Network %.0f FPS", NV_TENSORRT_MAJOR, NV_TENSORRT_MINOR, NV_TENSORRT_PATCH, precisionTypeToStr(net->GetPrecision()), net->GetNetworkFPS());
			display->SetTitle(str);

			// check if the user quit
			if( display->IsClosed() )
				signal_recieved = true;
		}

		// print out timing info
		net->PrintProfilerTimes();
	}
}

