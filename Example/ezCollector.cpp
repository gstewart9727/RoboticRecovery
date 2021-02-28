// Filename     : ezCollector.cpp
// Version      : 0.0.1
// Version Date : 10/30/2019
// Programmer   : Gabriel Stewart
// Description  : This file contains the source code for the ezCollector application. The tool allows users to collect images and
//                organize them for the purpose of creating a dataset.

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STBIW_ASSERT(x)

// Includes
#include "ezCollector.h"

// Globals
char classNames[10][100]; // WARNING - Must be larger than # of classes in .txt / Change to malloc
char types[3][6] {
    "train",
    "val",
    "test"
};
char cameraNum[PATH_MAX];
std::atomic<int> activeClass(0);
std::atomic<int> activeType(0);
std::atomic<int> currentInterval(0);
std::atomic<bool> running(false);
std::atomic<bool> ready(true);
char cwd[PATH_MAX];


// Function     : createStructure
// Description  : This function will store the class labels and create a directory structure for the images
// Parameters   : const char* labelArg - Command line argument containing labels.txt location
//                int intervalArg - Image capture delay
//                const char* cameraArg - Camera index
// Returns      : int - Indicating return status
int createStructure(const char* labelArg, int intervalArg, const char* cameraArg) {

    // Variable Declaration
    int classIndex = 0;
    char createDir[PATH_MAX];

    // Store location of labels.txt
    std::string labelDir(labelArg);
    std::string directory;
    const size_t last_slash_idx = labelDir.rfind('/');
    if (std::string::npos != last_slash_idx)
        directory = labelDir.substr(0, last_slash_idx);

    // Store data from command line arguments
    currentInterval = intervalArg;
    strcpy(cameraNum, cameraArg);

    // Copy directory to global variable
    strcpy(cwd, directory.c_str());

    // Create test, train and val folders
    mkdir((directory + "/test").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir((directory + "/train").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    mkdir((directory + "/val").c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    // Open file and parse class labels
    std::ifstream file(labelArg);
    if (file.good()) {
        std::string str;
        while (std::getline(file, str)) {

            // Copy name of class to array
            strcpy(classNames[classIndex], str.c_str());

            // Assemble directory path with class name, then create directory in each dataset folder
            strcpy(createDir, directory.c_str());
            strcat(createDir, ("/train/" + str).c_str());
            mkdir(createDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            strcpy(createDir, directory.c_str());
            strcat(createDir, ("/test/" + str).c_str());
            mkdir(createDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            strcpy(createDir, directory.c_str());
            strcat(createDir, ("/val/" + str).c_str());
            mkdir(createDir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

            classIndex++;
        }
    }
    else {
        printf("Label file not found. Please check filename and location before launching application.\n");
        return -1;
    }
    return 0;
}


// Function     : startCapture
// Description  : This function will either start the camera capture thread if it is not
//                running, or will stop it safely if it is.
// Parameters   : None
// Returns      : int - Indicating return status
int startCapture () {

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // If the camera is running, close it. Otherwise start it
    if (!running) {
        std::thread capture(collectRGBImages);
        capture.detach();
        running = true;
    }
    else {
        printf(" Shutting Down, please wait...\n");
        running = false;
    }
    // Set ready status to false so that menus do not appear while starting camera,
    // wait until status has been changed by thread to exit function
    ready = false;
    while (!ready) {}

    return 0;
}


// Function     : changeClass
// Description  : This function changes the active class being captured. Changes take effect next iteration
// Parameters   : None
// Returns      : None
void changeClass() {

    // Variable Declaration
    int x = 0, option = -1;

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // Display contents
    titleBar();
    printf("\t Please select class from one of the following options: \n");
    while (strcmp(classNames[x], "\0") != 0) {
        printf("\t  [%d] %s \n", x + 1, classNames[x]);
        x++;
    }
    printf("\t  [%d] (Return) \n", x + 1);

    // Allow user to select option, then act based on selection
    printf("\n\t Select option: ");
    std::cin >> option;

    if ((option - 1 != x) && !(option - 1 > x))
        activeClass = option - 1;
    else
        activeClass = 0;
}


// Function     : changeInterval
// Description  : This function changes the camera capture interval to a user selection. Changes take effect next iteration
// Parameters   : None
// Returns      : None
void changeInterval() {

    // Variable Declaration
    int option = 10;

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // Display contents
    titleBar();
    printf("\t Please enter new interval: ");

    // Allow user to select option, then act based on selection
    std::cin >> option;

    currentInterval = option;
}


// Function     : changeType
// Description  : This function changes the image type to a user selection
// Parameters   : None
// Returns      : None
void changeType() {

    // Shift contents of screen (clear screen)
    std::cout << "\x1b[2J\x1b[H";

    // Display contents
    titleBar();
    printf("\t Please select type from one of the following options: \n");

    for (int x = 0; x < 3; x++) {
        printf("\t  [%d] %s \n", x + 1, types[x]);
    }
    printf("\t  [4] (Return)\n");

    int option = 0;
    std::cin >> option;
    if (option == 1)
        activeType = 0;
    else if (option == 2)
        activeType = 1;
    else if (option == 3)
        activeType = 2;
    else
        activeType = 0;
}


// Function     : collectDepthImages
// Description  : This function will read depth images from a camera and store them into organized directories
// Parameters   : None
// Returns      : int - Indicating return status
int collectDEPTHImages() try {

    // Declare depth colorizer for pretty visualization of depth data
    rs2::colorizer color_map;

    // Declare RealSense pipeline, encapsulating the actual device and sensors
    rs2::pipeline pipe;

    // Start streaming with default recommended configuration
    pipe.start();

    // Capture 30 frames to give autoexposure, etc. a chance to settle
    for (auto i = 0; i < 30; ++i) pipe.wait_for_frames();

    // Wait for the next set of frames from the camera. Now that autoexposure, etc.
    // has settled, we will write these to disk
    for (auto&& frame : pipe.wait_for_frames())
    {
        // We can only save video frames as pngs, so we skip the rest
        if (auto vf = frame.as<rs2::video_frame>())
        {
            auto stream = frame.get_profile().stream_type();
            // Use the colorizer to get an rgb image for the depth stream
            if (vf.is<rs2::depth_frame>()) vf = color_map.process(frame);

            // Write images to disk
            std::stringstream png_file;
            png_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name() << ".png";
            stbi_write_png(png_file.str().c_str(), vf.get_width(), vf.get_height(),
                           vf.get_bytes_per_pixel(), vf.get_data(), vf.get_stride_in_bytes());
            std::cout << "Saved " << png_file.str() << std::endl;

//            std::stringstream jpg_file;
//            jpg_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name() << ".JPG";
//            stbi_write_jpg(jpg_file.str().c_str(), vf.get_width(), vf.get_width(), vf.get_bytes_per_pixel(), vf.get_data(), 95);
//            std::cout << "Saved " << jpg_file.str() << std::endl;

            // Record per-frame metadata for UVC streams
            std::stringstream csv_file;
            csv_file << "rs-save-to-disk-output-" << vf.get_profile().stream_name()
                     << "-metadata.csv";
            metadata_to_csv(vf, csv_file.str());
        }
    }
}
catch(const rs2::error & e)
{
    std::cerr << "RealSense error calling " << e.get_failed_function() << "(" << e.get_failed_args() << "):\n    " << e.what() << std::endl;
    return EXIT_FAILURE;
}
catch(const std::exception & e)
{
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
}
void metadata_to_csv(const rs2::frame& frm, const std::string& filename)
{
    std::ofstream csv;

    csv.open(filename);

    //    std::cout << "Writing metadata to " << filename << endl;
    csv << "Stream," << rs2_stream_to_string(frm.get_profile().stream_type()) << "\nMetadata Attribute,Value\n";

    // Record all the available metadata attributes
    for (size_t i = 0; i < RS2_FRAME_METADATA_COUNT; i++)
    {
        if (frm.supports_frame_metadata((rs2_frame_metadata_value)i))
        {
            csv << rs2_frame_metadata_to_string((rs2_frame_metadata_value)i) << ","
                << frm.get_frame_metadata((rs2_frame_metadata_value)i) << "\n";
        }
    }

    csv.close();
}


// Function     : collectRGBImages
// Description  : This function will read rgb images from a camera and store them into organized directories
// Parameters   : None
// Returns      : int - Indicating return status
void collectRGBImages() try {

    // Variable declaration
    gstCamera* camera;

    // Create and initialize camera device
    camera = gstCamera::Create(gstCamera::DefaultWidth, gstCamera::DefaultHeight, cameraNum);
    if(!camera) {
            printf("\nAnalysis:  failed to initialize camera device\n");
            throw std::exception();
    }

    printf("[Camera] successfully initialized camera device\n");
    printf("    width:  %u\n", camera->GetWidth());
    printf("   height:  %u\n", camera->GetHeight());
    printf("    depth:  %u (bpp)\n\n", camera->GetPixelDepth());

    // Open camera stream
    if(!camera->Open()) {
            printf("[Camera] failed to open camera for streaming\n");
            throw std::exception();
    }

    printf("[Camera] camera open for streaming\n");

    // These variables will be used to store the image data and dimensions.
    // The image data will be stored in shared CPU/GPU memory, so there are
    // pointers for the CPU and GPU (both reference the same physical memory)
    float* imgCPU    = NULL;    // CPU pointer to floating-point RGBA image data
    float* imgCUDA   = NULL;    // GPU pointer to floating-point RGBA image data
    int    imgWidth  = 0, imgHeight = 0;       // dimensions of the image (in pixels)

    CUDA(cudaDeviceSynchronize());

    // Delay to allow camera to focus/ adjust exposure
    sleep(5);

    // Create watchdog timer to catch application hangups
    signal(SIGALRM, watchdog);

    // Run capture loop for as long as it is instructed to run
    while (running) {

        // Start watchdog for double the capture interval
        alarm(currentInterval * 2);

        // Variables
        //char cwd[PATH_MAX];
        std::string filename;
        int quality = 95;
        float* imgRGBA = NULL;

        // Establish output file    name
        getcwd(cwd, sizeof(cwd));
        std::string string_cwd(cwd);
        filename = string_cwd;
        filename += "/";
        filename += types[activeType];
        filename += "/";
        filename += classNames[activeClass];
        filename += "/";
        std::time_t currTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        filename += std::ctime(&currTime);

        // Capture RGBA image
        if(!camera->CaptureRGBA(&imgRGBA, 1000, true)) {
                printf("Failed to capture RGBA image from camera\n");
                throw std::exception();
        }

        // After camera has taken an image we know it is fully initialized, so allow menu to print
        ready = true;

        // Save image to disk
        if(!saveImageRGBA((filename + ".JPG").c_str(), (float4*)imgRGBA, camera->GetWidth(), camera->GetHeight(), 255.0f)) {
                printf("Failed to save file. Please close and restart application. \n");
                throw std::exception();
        }

        sleep(currentInterval);

    }

    // Destroy resources
    ready = true;
    alarm(0);
    SAFE_DELETE(camera);
}
catch (std::exception e) {
    // If an exception is thrown, exit application
    std::exit(10);
}


// Function     : watchdog
// Description  : This is a watchdog which will throw an error code should it be called
// Parameters   : None
void watchdog(int sig)
{
    printf("\n WARNING! APPLICATION HAS TIMED OUT, SHUTTING DOWN...\n");
    std::exit(10);
}
