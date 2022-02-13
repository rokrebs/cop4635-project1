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
 * function to set the type and the correspoing status of the response
 */
void paketHandler::setTypeStatus() {
    if (r.uri == "/index.html") {
        a.status = "200";
        a.msg = "OK";
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
        a.msg = "NOT FOUND\n";
        r.uri = "/fake.html";
        readFile(r.uri);
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
    cout << "sent html file" << endl;
}

/*
 * function to set the error response for the client
 */
void paketHandler::setErr() {
    stringstream ss;
    ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
    ss << "Content-Type: texte/html\n";
    ss << "Content-Length: ";
    ss << a.length;
    ss << "\n\n";
    ss << a.content;
    responseToClient = ss.str();
    cout << "Error: Not found" << endl;
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
