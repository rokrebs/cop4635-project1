#include "paketHandler.hpp"

int a_l = 0;

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
  setRespose();
}

void paketHandler::setRespose() {
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

void paketHandler::setTypeStatus() {
  if (r.uri == "/index.html") {
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
	a.length = 13;
    a.status = "404";
    a.msg = "NOT FOUND\n";
	setErr();
	return;
  }
}

void paketHandler::setPicture() {
  stringstream ss;
  ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
  ss << "Content-Type: image/jpeg\n";
  ss << "Content-Length: ";
  ss << a.length;
  ss << "\n\n";
  ss << a.content;
  responseToClient = ss.str();
}
void paketHandler::setHtml() {
  stringstream ss;
  ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
  ss << "Content-Type: text/html\n";
  ss << "Content-Length: ";
  ss << a.length;
  ss << "\n\n";
  ss << a.content;
  printf("%s\n",(char*)(ss.str()).c_str());
  responseToClient = ss.str();
}
void paketHandler::setErr() {
  stringstream ss;
  ss << a.protocolV << " " << a.status << " " << a.msg << "\n";
  ss << "Content-Type: text/plain\n";
  ss << "Content-Length: 13\n";
  ss << "\n";
  ss << "404 Not Found\n";
  responseToClient = ss.str();
}

void paketHandler::readFile(string location) {
  location = location.erase(0, 1);
	//string path = location;
  ifstream is(location, ifstream::binary);
  if (is) {
    /* // get length of file:
     is.seekg(0, is.end);
     a.length = is.tellg();
     is.seekg(0, is.beg);

     char *buffer = new char[a.length];
     // read data as a block:
     is.read(buffer, a.length);
     return buffer;*/
    std::stringstream fs;
    fs << is.rdbuf();
    std::string o = fs.str();
	is.close();
	a.length = (int)o.size();
    a.content = o;
  }
}

string paketHandler::printMsg() { return responseToClient; }
