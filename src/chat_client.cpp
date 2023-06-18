#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

void receive_messages(int sock) {
    char server_reply[1000];
    while (1) {
        // receive reply from the server
        if (recv(sock, server_reply, 1000, 0) < 0) {
            std::cout << "Recv failed" << std::endl;
            break;
        }

        std::cout << server_reply << std::endl;
        memset(server_reply, 0, sizeof(server_reply));
    }
}

int main() {
    int sock;
    struct sockaddr_in server;

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

    // detach thread to continously receive messages from the server
    std::thread recv_thread(receive_messages, sock);
    recv_thread.detach();

    // communicate with the server
    while (1) {
        std::string message;
        std::getline(std::cin, message); // user chat message ends with newline (press enter = send message)
         
        // send the message to the server
        if (send(sock, message.c_str(), 1000, 0) < 0) {
            std::cout << "Send failed" << std::endl;
            break;
        }        
    }

    close(sock);
    return 0;
}