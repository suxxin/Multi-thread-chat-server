#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char server_reply[1000];

    // create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cout << "Could not create socket" << std::endl;
        return 1;
    }
    // spcify the network address and port to connect the socket to
    server.sin_family = AF_INET;                        // IPv4
    server.sin_addr.s_addr = inet_addr("127.0.0.1");    // IP address of the server (local)
    server.sin_port = htons(8888);                      // port# = 8888 

    // connect to server
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // communicate with the server
    while (1) {
        std::cout << "Enter message: ";
        std::string message;
        std::getline(std::cin, message); // user chat message ends with newline (press enter = send message)
         
        // send the message to the server
        if (send(sock, message.c_str(), 1000, 0) < 0) {
            std::cout << "Send failed" << std::endl;
            break;
        }

        // receive reply from the server
        if (recv(sock, server_reply, 1000, 0) < 0) {
            std::cout << "Recv failed" << std::endl;
            break;
        }

        std::cout << "Server reply: " << server_reply << std::endl;
        memset(server_reply, 0, sizeof(server_reply));
    }

    close(sock);
    return 0;
}