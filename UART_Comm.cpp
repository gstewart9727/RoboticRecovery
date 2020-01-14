// Filename   : UART_Comm.cpp
// Date       : January 9th, 2020
// Programmer : Gabriel Stewart
// Description: This file contains the source code for UART communication from the Jetson nano
//              to the 6DOF robotic arm. 
// Sources    : [1] https://devtalk.nvidia.com/default/topic/1057441/jetson-nano/jetson-nano-uart-c-c-example/2
//                  User posted an example of succesful connection between the Nano's J41 headers for UART and an 
//                  arduino. This example is used for a reference in establishing UART connection to microcontroller.


// Included Header Files
#include <stdio.h>
#include <unistd.h>       // Used for UART
#include <sys/fcntl.h>    // Used for UART
#include <termios.h>      // Used for UART
#include <string>

using namespace std; // Should be removed at later date


// Define Constants
const char *uart_target = "/dev/ttyTHS1";
#define     NSERIAL_CHAR   256
#define     VMINX          1
#define     BAUDRATE       B9600 // Communication protocol required 9600 baud


// Function     : main
// Description  : 
// Parameters   :
// Returns      :
int main()
{
	// Declare UART required vars
  int fid = -1;
	struct termios  port_options;   // Create the structure                          

  tcgetattr(fid, &port_options);	// Get the current attributes of the Serial port 

	
  //------------------------------------------------
  //  OPEN THE UART [1]
  //------------------------------------------------
  // The flags (defined in fcntl.h):
  //	Access modes (use 1 of these):
  //		O_RDONLY - Open for reading only.
  //		O_RDWR   - Open for reading and writing.
  //		O_WRONLY - Open for writing only.
  //	  O_NDELAY / O_NONBLOCK (same function) 
  //               - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
  //                 if there is no input immediately available (instead of blocking). Likewise, write requests can also return
  //				   immediately with a failure status if the output can't be written immediately.
  //                 Caution: VMIN and VTIME flags are ignored if O_NONBLOCK flag is set.
  //	  O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.fid = open("/dev/ttyTHS1", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode

  // Assign UART connection to fid
  fid = open(uart_target, O_RDWR | O_NOCTTY );

	tcflush(fid, TCIFLUSH);
 	tcflush(fid, TCIOFLUSH);
 	
  usleep(1000000);  // 1 sec delay

  // If error occured during opening of UART
  if (fid == -1)
	{
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}
	
  //------------------------------------------------
  // CONFIGURE THE UART [1]
  //------------------------------------------------
  // flags defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html
  //	Baud rate:
  //         - B1200, B2400, B4800, *B9600, B19200, B38400, B57600, B115200, 
  //           B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, 
  //           B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
  //	CSIZE: - CS5, CS6, CS7, CS8
  //	CLOCAL - Ignore modem status lines
  //	CREAD  - Enable receiver
  //	IGNPAR = Ignore characters with parity errors
  //	ICRNL  - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for bianry comms!)
  //	PARENB - Parity enable
  //	PARODD - Odd parity (else even)

    port_options.c_cflag &= ~PARENB;            // Disables the Parity Enable bit(PARENB),So No Parity   
    port_options.c_cflag &= ~CSTOPB;            // CSTOPB = 2 Stop bits,here it is cleared so 1 Stop bit 
    port_options.c_cflag &= ~CSIZE;	            // Clears the mask for setting the data size             
    port_options.c_cflag |=  CS8;               // Set the data bits = 8                                 	 
    port_options.c_cflag &= ~CRTSCTS;           // No Hardware flow Control                         
    port_options.c_cflag |=  CREAD | CLOCAL;                  // Enable receiver,Ignore Modem Control lines       				
    port_options.c_iflag &= ~(IXON | IXOFF | IXANY);          // Disable XON/XOFF flow control both input & output
    port_options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Non Cannonical mode                            
    port_options.c_oflag &= ~OPOST;                           // No Output Processing

    port_options.c_lflag = 0;               //  enable raw input instead of canonical,
 		
    port_options.c_cc[VMIN]  = VMINX;       // Read at least 1 character
    port_options.c_cc[VTIME] = 0;           // Wait indefinetly 
		
    cfsetispeed(&port_options,BAUDRATE);    // Set Read  Speed 
    cfsetospeed(&port_options,BAUDRATE);    // Set Write Speed 

    // Set the attributes to the termios structure
    int att = tcsetattr(fid, TCSANOW, &port_options);

    if (att != 0 )
    {
        printf("\nERROR in Setting port attributes");
    }
    else
    {
        printf("\nSERIAL Port creation successful.\n");
    }

    // Flush Buffers
    tcflush(fid, TCIFLUSH);
    tcflush(fid, TCIOFLUSH);

    usleep(500000);   // 0.5 sec delay


    //--------------------------------------------------------------
    // TRANSMITTING BYTES
    //--------------------------------------------------------------
    unsigned char tx_buffer[20];
    unsigned char *p_tx_buffer;
	
    p_tx_buffer = &tx_buffer[0];

    *p_tx_buffer++ = 0x55; // Header 1
    *p_tx_buffer++ = 0x55; // Header 2
    *p_tx_buffer++ = 0x08; // Length
    *p_tx_buffer++ = 0x03; // Command
    *p_tx_buffer++ = 0x01; // Number of servos in command
    *p_tx_buffer++ = 0xD0; // Lower 8 bits of time val
    *p_tx_buffer++ = 0x07; // Higher 8 bits of time val
    *p_tx_buffer++ = 0x01; // Servo ID number
    *p_tx_buffer++ = 0xC4; // Lower 8 bits of angle pos value
    *p_tx_buffer++ = 0x09; // Higher 8 bits of angle pos value


    printf("fid 1=%d\n", fid );
	
	if (fid != -1)
	{
		int count = write(fid, &tx_buffer[0], (p_tx_buffer - &tx_buffer[0]));		//Filestream, bytes to write, number of bytes to write

    usleep(1000);   // .001 sec delay

    printf("Count = %d\n", count);

		if (count < 0) {
      printf("UART TX error\n");
    }  
	}

  usleep(1000000);  // 1 sec delay

  // Close UART
  close(fid);
}