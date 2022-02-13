/*
 * @autor Rocio Krebs
 *
 */

#include "paketHandler.hpp"

paketHandler::paketHandler(char *buffer) {
    responseToClient = "";
    splitChar(buffer);
}

void paketHandler::splitChar(char *buffer) {
    std::string item;
    std::stringstream ss(buffer);

    while (ss >> item) {
        content.push_back(item);
    }
    setResponse();
}

void paketHandler::setResponse() {
    int i = 0;
    r.method = content.at(i++);
    r.uri = content.at(i++);
    r.protocolV = content.at(i);
    setRequest();
}

void paketHandler::setRequest() {
    a.protocolV = r.protocolV;
    setTypeStatus();
}

/*
 * function to set the type and the corresponding status of the response
 */
void paketHandler::setTypeStatus() {
    if (r.uri == "/") {
        a.status = "200";
        a.msg = "OK";
        r.uri = "/index.html";
        readFile(r.uri);
        setHtml();
        return;
    } else if (r.uri == "/working.html") {
        a.status = "200";
        a.msg = "OK";
        readFile(r.uri);
        setHtml();
        return;
    } else if (r.uri.compare("/dragon.jpeg") == 0) {
        a.status = "200";
        a.msg = "OK";
        readFile(r.uri);
        setPicture();
        return;
    } else {
        a.status = "404";
        a.msg = "Not Found\n";
        setErr();
        return;
    }
}

/*
 * function to set a picture ready for the client
 */
void paketHandler::setPicture() {
    stringstream ss;
    ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
    ss << "Content-Type: image/jpeg\n";
    ss << "Content-Length: ";
    ss << a.length;
    ss << "\n\n";
    ss << a.content;
    responseToClient = ss.str();
    cout << "sent picture" << endl;
}

/*
 * function to set the html for the client
 */
void paketHandler::setHtml() {
    stringstream ss;
    ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
    ss << "Content-Type: text/html\n";
    ss << "Content-Length: ";
    ss << a.length;
    ss << "\n\n";
    ss << a.content;
    responseToClient = ss.str();
    cout << "sent "<< r.uri<<" file" << endl;
}

/*
 * function to set the error response for the client
 */
void paketHandler::setErr() {
    responseToClient = "HTTP/1.1 404 Not Found\nContent-Type: text/plain\nContent-Length: 21\n\nERROR: 404 NOT FOUND.";
    cout << "sent error message "<< endl;
}

/*
 * function to read each content of the requested file
 */
void paketHandler::readFile(string location) {
    location = location.erase(0, 1);
    ifstream is(location, ifstream::binary);
    if (is) {
        std::stringstream fs;
        fs << is.rdbuf();
        std::string o = fs.str();
        is.close();
        a.length = (int) o.size();
        a.content = o;
    }
}

string paketHandler::printMsg() {
    return responseToClient;
}
