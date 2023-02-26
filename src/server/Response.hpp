#ifndef REPONSE_H
# define REPONSE_H
# include <string.h>

enum Method { DEFAULT, GET, HEAD, POST, PUT, DELETE, OPTIONS, TRACE };
enum URIType { DIRECTORY, MYFILE, FILE_TO_CREATE, CGI_PROGRAM };
enum TransferType { GENERAL, CHUNKED };
enum Phase { READY, ON_HEADER, ON_BODY, COMPLETE };

class Response
{
private:

public:
	Response(/* args */);
	~Response();
};

#endif