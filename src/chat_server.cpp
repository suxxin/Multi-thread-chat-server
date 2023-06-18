#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_socket, client_socket;
    /** 
    struct sockaddr_in {
        short            sin_family;   // address family (AF_INET)
        unsigned short   sin_port;     // port number
        struct in_addr   sin_addr;     // IP address
        char             sin_zero[8];  // padding
    };
    **/
    struct sockaddr_in server, client;

    // create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cout << "Could not create socket" << std::endl;
        return 1;
    }
    // spcify the network address and port to connect the socket to
    server.sin_family = AF_INET;            // IPv4
    server.sin_addr.s_addr = INADDR_ANY;    // accept client connections from all network interfaces on the machine where the server is running (set to this machine's IP address)
    server.sin_port = htons(8888);          // port# = 8888 
    
    // bind
    if (bind(server_socket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // listen
    listen(server_socket, 3); // handles 3 connection requests simultaneously

    std::cout << "Waiting for incoming connections..." << std::endl;
    int c = sizeof(struct sockaddr_in);
    // accept
    while ( (client_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t*)&c))) {
        char client_message[1000];
        int read_size;
        
        // receive a message from client
        while ((read_size = recv(client_socket, client_message, 1000, 0)) > 0) {
            // log client's message 
            // TODO: more prfessional log methoid? 
            std::cout << client_message << std::endl;
            // echo back to the client
            write(client_socket, client_message, strlen(client_message));
            memset(client_message, 0, 1000);
        }

        if (read_size == 0) {
            std::cout << "Client disconnected" << std::endl;
        } else if (read_size == -1) {
            perror("Recv failed");
            break;
        }
    }
    close(server_socket);
    return 0;
}