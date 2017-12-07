/*
 * Naama Harshoshanim
 * 315783217
 * Tchelet Englman
 * 208780585
 */

#ifndef EX3_SERVER_H
#define EX3_SERVER_H


class Server {
public:
    Server(int port);
    void start();
    void stop();

private:
    int port;
    int serverSocket;
    void handleClient(int clientSocket, int clientSocket2);
};


#endif //EX3_SERVER_H
