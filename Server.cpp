/*
 * Naama Harshoshanim
 * 315783217
 * Tchelet Englman
 * 208780585
 */

#include "Server.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
using namespace std;
#define MAX_CONNECTED_CLIENT 2

Server::Server(int port) : port(port), serverSocket(0) {
    cout << "Server" << endl;
}

void Server::start() {
    //create a socket point
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        throw "Error opening socket";
    }
    // assign a local address to the socket
    struct sockaddr_in serverAddress;
    bzero((void *)&serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(port);
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        throw "Error on binding";
    }
    // start listening to incoming connections
    listen(serverSocket, MAX_CONNECTED_CLIENT);
    // define the client socket's structures
    struct sockaddr_in clientAddress1;
    struct sockaddr_in clientAddress2;
    socklen_t clientAddressLen1 = sizeof((struct sockaddr*) &clientAddress1);
    socklen_t clientAddressLen2 = sizeof((struct sockaddr*) &clientAddress2);
    while (true) {
        cout << "Waiting for client connections..." << endl;
        // accept a new client connection
        int clientSocket1 = accept(serverSocket,
                                  (struct sockaddr*)&clientAddress1, &clientAddressLen1);
        int clientSocket2 = accept(serverSocket,
                                   (struct sockaddr*)&clientAddress2, &clientAddressLen2);
        cout << "Clients connected" << endl;
        if (clientSocket1 == -1 || clientSocket2 == -1) {
            throw "Error on accept";
        }
        handleClient(clientSocket1, clientSocket2);
        //close communication with the client
        close(clientSocket1);
        close(clientSocket2);
    }
}

void Server::handleClient(int clientSocket1, int clientSocket2) {
    write(clientSocket1, "1", sizeof(char));
    write(clientSocket2, "2", sizeof(char));
    char input1[7] = "";
    char input2[7] = "";
    while (strcmp(input1, "End") != 0 && strcmp(input2, "End") != 0) {
        ssize_t n = read(clientSocket1, &input1, sizeof(input1));
        if (n == -1) {
            cout << "Error reading x" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        cout << *input1 << endl;
        write(clientSocket2, &input1, n);
        n = read(clientSocket2, &input2, sizeof(input2));
        if (n == -1) {
            cout << "Error reading x" << endl;
            return;
        }
        if (n == 0) {
            cout << "Client disconnected" << endl;
            return;
        }
        write(clientSocket1, &input2, n);
    }
}

void Server::stop() {
    close(serverSocket);
}