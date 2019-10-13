
## Compilation

A makefile to compile both my .c files (http_server.c and http_client.c) has been provided. To compile, open your terminal and cd into the folder my project resides in. 
The command "make" with compile the project. 
If you type "make" after the project has already been compiled, you will receive the message "make: Nothing to be done for `all'.". This is not an error, it is just saying the compilation has already taken place!




## Running

To run my project, you will need two terminals open (cd'ed to the folder of my project), and to have compiled my project once. 

Start the server first, by typeing the command "./http_server [port_number]", replacing the brackets with the port number of your choice. 

Note: on a Mac, I can tell once my server has started completely when the buffer in the terminal has stopped spinning. I am unsure if other OSs will display this similarly, so for reference the server will usually take about 10 seconds to boot up properly. If a client tries to connect before this time, they are sometimes refused, so I find it best to wait a few seconds. 

Once the server has started, you may move to the other terminal and type the command "./http_client [flags] [host] [port_number], where [flags] may be the option "-p" to print the RTT it takes to make a connection, [host] is the name of the host you wish to connect to (either a valid URL or an IP address), and [port_number] is the port number the server is running on. 

Please note that if entering a URL, to only enter the base URL (e.g. www.google.com instead of www.google.com/index.html, or rambo.wpi.edu instead of rambo.wpi.edu/TMDG.html). An IP address requires no additional directions. To run locally, use IP 127.0.0.1. 




## Additional Notes

Unfortunately, due to my own misunderstanding of a portion of the project, I was forced to redo a large part, and ran out of time. Subsequently, there are many quirks to this program I was unable to resolve. I apologize for any inconvenience these may you, the grader. 

- When using the client to contact an outside host (www.google.com, www.mit.edu), the program does not terminate once the whole file is received. Although my client does fetch the complete file, you will have to manually exit in the terminal via command + c. 

- My program is only able to make requests for index.html files. When testing, I used the TMDG.html locally, but changed the name to index.html, and ran out of time before I was able to write the code to handle index.html vs TMDG.html, or parse these routes after the "/" proceeding the base HTML. Therefore, for testing purposes I ask that a file named index.html is used, even if the TMDG file must be renamed. For convenience, I have provided my renamed index.html file in the submission .zip. I hope this is allowed, although the project did not explicitly forbid it, and I apologize again for the inconvenience. 

- Finally, although my programs run fine locally, I could not run them once uploaded to the WPI servers. I attempted rambo and linux, and was ultimately not able to resolve these issues. Because my project is able to execute correctly in a local environment, I hope that the penalty for this will be somewhat lien ant, and I will be proactive in testing on the WPI servers in the future. 