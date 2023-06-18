# Simple Chat Server

This chat server/client example is written in C++ using the basic concepts of network programming and communication between client and server over TCP/IP protocols.

This server is designed to handle multiple clients simultaneously by using multithreading. \
It accepts messages from clients and broadcasts them to all connected clients.

## Technical Choices

This program utilizes TCP/IP socket programming. The server and client exchange data using the TCP protocol. 

TCP ensures sequential and reliable data transfer, which are significant to a chat application.

It is important that the messages delivered correctly in order.

Also, this application uses IPv4 which is widely used and supported by most network devices and systems. 

## How it Works

The server calls functions such as `socket()`, `bind()`, `listen()`, `accept()` to accept connection requests from the client, and uses `read()` and `write()` functions to exchange data with the client.

The client calls `socket()` and `connect()` functions to request a connection to the server, and uses `send()` and `recv()` functions to exchange data with the server.


## Installation

Clone the repository:
```bash
git clone https://github.com/suxxin/Muti-thread-chat-server.git
```

Build the project:
``` bash
cd Multi-thread-chat-server
make
```

## Usage

Start the server:
``` bash
./bin/chat_server
```

Start the client in a new terminal:
``` bash
./bin/chat_client
```

Enter your message in the client terminal.
