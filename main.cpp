/*
 * Naama Harshoshanim
 * 315783217
 * Tchelet Englman
 * 208780585
 */

#include "Server.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
    Server server(8000);
    ofstream outFile;
    outFile.open("definition.txt");
    outFile << "8000" << endl;
    outFile << "127.0.0.1" << endl;
    outFile.close();
    try {
        server.start();
        server.stop();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason:" << msg << endl;
    }
    exit(-1);
}