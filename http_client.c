#include "client_header.h"

// Error Handling
void DieWithError(char *errorMessage) {
    printf("%s\n", errorMessage);
    exit(1);
}

// Convert URL to IP address
int HostToIP(char *servHost, char *ip) {
    struct addrinfo hints, *infoptr;
    //hints.ai_family = AF_INET;
    
    
    // Use getaddrinfo to find crresponding IP to hostname
    int result = getaddrinfo(servHost, NULL, &hints, &infoptr);
    // If error
    if (result) {
        fprintf(stderr, "getaddrinfp: %s\n", gai_strerror(result));
        exit(1);
    }
    struct addrinfo *p;
    char host[256];
    for(p = infoptr ; p !=NULL; p = p->ai_next) {
        getnameinfo(p->ai_addr, p->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
    }
    freeaddrinfo(infoptr);
    strcpy(ip , host );
    
    return 0;
}

char servIP [250] = "base";

int main(int argc, char *argv[]) {
    int sock;                       // Socket
    struct sockaddr_in serverURL;   // Server address
    unsigned short portNumber;      // Port number
    char *servHost;                 // Server host
    char echoBuffer[RCVBUFSIZE];    // Buffer for incoming message
    int bytesRcvd, totalBytesRcvd;  // Bytes read in single recv(), total bytes read
    
    // Test for correct number of args
    if ((argc < 3) || (argc > 4)) {
        fprintf(stderr, "Usage: %s [-options] <Server IP> <Port Number>\n",
                argv[0]);
        exit(1);
    }
    // Assign variables based on argument number
    if (argc == 3) {
        servHost = argv[1];
        portNumber = atoi(argv[2]);
    }
    else if (argc ==4) {
        servHost = argv[2];
        portNumber = atoi(argv[3]);
    }
    
    // Create HTTP request message
    char middle[1000] = "";
    char message2[1000] = "";
    char first[] = "GET /index.html HTTP/1.1\r\nHost:"; // CHANGE TO TMDG.HTML HERE
    
    strcat(message2, first);
    strcat(message2, servHost);
    strcpy(middle, "\r\n\r\n");
    strcat(message2, middle);
    
    char *message = message2;
    
    // Create a TCP socket
    if ((sock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        DieWithError("socket() failed");
    }
    
    // Call and assign hostname -> IP translation
    char ip[100];
    HostToIP(servHost, ip);
    strcpy(servIP, ip);
    printf("ip address for rambo = %s", servIP);
    
    // Create server address to connect to
    memset(&serverURL, 0, sizeof(serverURL));
    serverURL.sin_family = AF_INET;
    serverURL.sin_addr.s_addr = inet_addr(servIP);//"127.0.0.1"); // needs to change
    serverURL.sin_port = htons(portNumber);
    
    // Set up time variables to track time to connect to server
    struct timeval start, end;
    gettimeofday(&start, NULL);
    // Establish connection to server
    if (connect (sock, (struct sockaddr *) &serverURL, sizeof(serverURL)) < 0)
        DieWithError("connect() failed");
    gettimeofday(&end, NULL);
    double total_time;
    total_time = (end.tv_sec - start.tv_sec) * 1e3;
    total_time = (total_time + (end.tv_usec - start.tv_usec)) * 1e-3;
    // Display if options was passed in as arg
    if (argc == 4) {
        printf("\nTotal time to connect to server was %f milliseconds\n\n", total_time);
    }
    
    // Error
    if (send (sock, message, strlen(message), 0) < 0) {
        DieWithError("send() failed");
    }
    // Recieve server response
    totalBytesRcvd = 0;
    printf("Received: ");
    
    do {
        bytesRcvd = recv(sock, echoBuffer, 1024, 0) ;
        totalBytesRcvd += bytesRcvd;
        echoBuffer[bytesRcvd] = '\0';
        
        printf("%s", echoBuffer);
        if (bytesRcvd == 0) {
            break;
        }
        if (bytesRcvd == -1) {
            DieWithError("recv() failed or connection closed prematurely");
        }
    } while (bytesRcvd > 0);
    
    printf("\n");
    close (sock);
    exit(0);
} 
