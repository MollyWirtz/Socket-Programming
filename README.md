# Socket Programming
CS 3516 Project 1

This prject imlpements an HTTP client and server running a simplified version of the HTTP/1.1 protocol. 


## Compilation

A makefile to compile both my .c files (http_server.c and http_client.c) has been provided. To compile, open your terminal and cd into the folder my project resides in. 
The command "make" with compile the project.


## Running

To run my project, you will need two terminals open (cd'ed to the folder of my project), and to have compiled my project once. 

Start the server first, by typeing the command "./http_server [port_number]", replacing the brackets with the port number of your choice. 

Note: on a Mac OS, I can tell once my server has started completely when the buffer in the terminal has stopped spinning. I am unsure if other OSs will display this similarly, so for reference the server will usually take about 10 seconds to boot up properly. If a client tries to connect before this time, they are sometimes refused, so I find it best to wait a few seconds. 

Once the server has started, you may move to the other terminal and type the command "./http_client [flags] [host] [port_number], where [flags] may be the option "-p" to print the RTT it takes to make a connection, [host] is the name of the host you wish to connect to (either a valid URL or an IP address), and [port_number] is the port number the server is running on. 

Please note that if entering a URL, to only enter the base URL (e.g. www.google.com instead of www.google.com/index.html, or rambo.wpi.edu instead of rambo.wpi.edu/TMDG.html). An IP address requires no additional directions. To run locally, use IP 127.0.0.1. 



## Additional Notes

- When using the client to contact an outside host (www.google.com, www.mit.edu), the program does not terminate once the whole file is received. Although my client does fetch the complete file, you will have to manually exit in the terminal via command + c. 
