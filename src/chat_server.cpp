#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <unordered_map>

std::unordered_map<std::string, std::string> client_map; // maps < sin_addr:port -> client # >

void handle_client(int client_socket, std::string sin_addr, std::string sin_port) {
    char client_message[1000];
    int read_size;

    // new client 
    std::cout << "New client connected: " << sin_addr << ":" << sin_port << std::endl;
    std::string client_addr_port = sin_addr + ":" + sin_port;
    client_map[client_addr_port] = "client" + std::to_string(client_map.size());

    // receive a message from client
    while ((read_size = recv(client_socket, client_message, 1000, 0)) > 0) {
        // log client's message 
        // TODO: more prfessional log methoid? 
        std::cout << client_map[client_addr_port] << ":" << client_message << std::endl;
        // echo back to the client
        write(client_socket, client_message, strlen(client_message));
        memset(client_message, 0, 1000);
    }

    if (read_size == 0) {
        std::cout << "Client disconnected" << std::endl;
    } else if (read_size == -1) {
        perror("Recv failed");
    }

    close(client_socket);
}

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
    while ( (client_socket = accept(server_socket, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        // the arguments are "copied" to the new thread
        std::string sin_addr = std::string(inet_ntoa(client.sin_addr));
        std::string sin_port = std::to_string(ntohs(client.sin_port));
        // create a thread
        std::thread client_thread(handle_client, client_socket, sin_addr, sin_port);
        client_thread.detach(); // individually process each client
    }
    close(server_socket);
    return 0;
}