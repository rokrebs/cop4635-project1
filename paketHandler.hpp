/*
 * @autor Rocio Krebs
 *
 */
#ifndef PAKETHANDLER_HPP
#define PAKETHANDLER_HPP

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

class paketHandler {
    struct request {
        string method;
        string uri;
        string protocolV;
    };

    struct response {
        string protocolV;
        string status;
        string msg;
        string content;
        int length;
    };

private:
    vector <string> content;
    struct request r;
    struct response a;
    string responseToClient;

    void splitChar(char *buffer);

    void setTypeStatus();

    void setPicture();

    void setHtml();

    void setErr();

    void readFile(string location);

    void setResponse();

    void setRequest();

public:
    paketHandler(char *buffer);

    string printMsg();

};

#endif