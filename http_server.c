#include "server_header.h"

// Error Handling
void DieWithError(char *errorMessage) {
    printf("%s\n", errorMessage);
    exit(1);
}

// Handle clients coneected via TCP
void HandleTCPClient(int clntSocket) {
    char buffer[1024] = {0};
    char host[1024] = {0};
    
    int clntRead = read(clntSocket, buffer, 1024);
    printf("\nClient request:\n");
    
    printf("%s\n", buffer);
    if (clntRead < 0) {
        DieWithError("Empty request recieved from client.");
    }
    
    // Handling index.html file
    FILE* fp=fopen("index.html","r");
    // File size info
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char sampleFile [sz] ;
    char c = fgetc(fp);
    // Read file into string char by char
    while (c != EOF) {
        int len = strlen(sampleFile);
        sampleFile[len] = c;
        sampleFile[len+1] = '\0';
        c = fgetc(fp);
    }

    // Create HTTP resonse message
    char finalMessage [1024] ;
    const char * returnMessage =
    "HTTP/1.1 200 OK\n"
    "Content-Type: text/plain\n"
    "Content-Length: 34\n"
    "\n"
    "sampleFile=%s";
    
    char middle[60000] = "";
    char message2[60000] = "";
    char first[] = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 58327\n\n";

    strcat(message2, first);
    strcat(message2, sampleFile);

    char *message = message2;
    
    // Send request message, close socket
    send(clntSocket , message, strlen(message) , 0 );
    printf("Message sent!\n");
    printf("Waiting for new client...\n") ;
    close(clntSocket);
}

int main(int argc, char *argv[]) {
    int servSock;                       // Server Socket
    int clntSock;                       // CLient Socket
    struct sockaddr_in echoServAddr;    // Local address
    struct sockaddr_in echoClntAddr;    // Client address
    unsigned short echoServPort;        // Server port
    unsigned int clntLen;               // Length of client address struct
    
    // If correct number of args
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <Server Port>\n", argv[0]);
        exit(1);
    }
    
    // Set port
    echoServPort = atoi(argv[1]);
    // Create server socket
    if ((servSock = socket (PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
        DieWithError("socket() failed");
    
    
    // Cteate server address struct
    memset(&echoServAddr, 0, sizeof(echoServAddr));
    echoServAddr.sin_family = AF_INET;
    echoServAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//"130.215.36.155");//127.0.0.1");//htonl(INADDR_ANY);
    echoServAddr.sin_port = htons(echoServPort);
    // Bind to the server address
    if (bind (servSock, (struct sockaddr *) &echoServAddr, sizeof(echoServAddr))<0)
        DieWithError("bind() failed");
    // Have socket listen for connections
    if (listen (servSock, MAXPENDING) < 0)
        DieWithError("listen() failed");
    
    for (;;) {
        clntLen = sizeof(echoClntAddr);
        // Accpet connecting client
        if ((clntSock = accept (servSock, (struct sockaddr *) &echoClntAddr, &clntLen)) < 0)
            DieWithError("accept() failed");
        printf("Handling client %s\n", inet_ntoa(echoClntAddr.sin_addr));
        HandleTCPClient(clntSock);
    }
}
