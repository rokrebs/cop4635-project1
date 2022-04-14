# http-server

## OVERVIEW

The objective of this project is to demonstrate the interactions between an HTML server with a Web
Browser(HTML client)

## THE PROGRAMS

The HTTP server system consists of one program( the httpServer). The httpServer program serves HTML files to the
Browser.

## IMPLEMENTATION

Program an HTTP server in C++. The server will listen on a valid port. Make sure you use a port number from the
valid port number range (60001 – 60099). When a client makes a request for an HTML file using a valid HTTP/1.1
method like ‘GET’, the HTTP server will check if the file is a valid HTML file with the server. If the file is a valid HTML
file, the server should send it to the client with proper http header. If the file requested by the client is not a valid
file with the server, or if the client request for the file is not recognized, the server should respond with a small, but
descriptive error message that should be received by the client and displayed. Your HTTP server should be verbose,
and display all activity going on at the server.
To test the file access through the server further, make sure you incorporate two hyperlinks in the requested html
file. Make the first link point to an image object that gets displayed on the client browser on clicking the link. Make
the other link on the html page point to a non-existent html page.
