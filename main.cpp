/*
 * Naama Harshoshanim
 * 315783217
 * Tchelet Englman
 * 208780585
 */

#include "Server.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

int main() {
    Server server(8000);
    try {
        server.start();
        server.stop();
    } catch (const char *msg) {
        cout << "Cannot start server. Reason:" << msg << endl;
    }
    exit(-1);
}