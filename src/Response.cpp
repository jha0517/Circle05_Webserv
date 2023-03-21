/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/21 11:44:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Response.hpp"

Response::Response()
{
	statusCodeDic.insert(std::pair<int, std::string>(200, "OK"));
	statusCodeDic.insert(std::pair<int, std::string>(400, "Bad Request"));
	statusCodeDic.insert(std::pair<int, std::string>(403, "Forbidden"));
	statusCodeDic.insert(std::pair<int, std::string>(404, "Not Found"));
	statusCodeDic.insert(std::pair<int, std::string>(405, "Method Not Allowed"));
	statusCodeDic.insert(std::pair<int, std::string>(500, "Internal Server Error"));
	statusCodeDic.insert(std::pair<int, std::string>(505, "HTTP Version Not Supported"));
    this->mimeMap.insert(std::make_pair("aac", "audio/aac"));
    this->mimeMap.insert(std::make_pair("abw", "application/x-abiword"));
    this->mimeMap.insert(std::make_pair("arc", "application/x-freearc"));
    this->mimeMap.insert(std::make_pair("avi", "video/x-msvideo"));
    this->mimeMap.insert(std::make_pair("bin", "application/octet-stream"));
    this->mimeMap.insert(std::make_pair("bmp", "image/bmp"));
    this->mimeMap.insert(std::make_pair("bz2", "application/x-bzip2"));
    this->mimeMap.insert(std::make_pair("csh", "application/x-csh"));
    this->mimeMap.insert(std::make_pair("css", "text/css"));
    this->mimeMap.insert(std::make_pair("csv", "text/csv"));
    this->mimeMap.insert(std::make_pair("doc", "application/msword"));
    this->mimeMap.insert(std::make_pair("gif", "image/gif"));
    this->mimeMap.insert(std::make_pair("htm", "text/html"));
    this->mimeMap.insert(std::make_pair("html", "text/html"));
    this->mimeMap.insert(std::make_pair("jpeg", "image/jpeg"));
    this->mimeMap.insert(std::make_pair("jpg", "image/jpg"));
    this->mimeMap.insert(std::make_pair("mpeg", "video/mpeg"));
    this->mimeMap.insert(std::make_pair("png", "image/png"));
    this->mimeMap.insert(std::make_pair("php", "application/x-httpd-php"));
    this->mimeMap.insert(std::make_pair("pdf", "application/pdf"));
    this->mimeMap.insert(std::make_pair("txt", "text/plain"));
}

Response::~Response()
{
}

std::string	check_filename_get_str(const char *filename)
{
	std::string		src;
	std::string		buffer;
	std::ifstream	ifs;
	char	c;
	
	// if (checkPathRelative())
	ifs.open(filename);
	if (!ifs)
	{
		std::cout << "File non-existance or Right Denied!" << std::endl;
		return ("404");
	}
	while (ifs.get(c))
		src+= c;
	ifs.close();
	if (src.empty())
	{
		std::cout << "File is empty!" << std::endl;
		return ("");
	}
	return (src);
}

std::string intToString(int a)
{
	std::stringstream	ss;

    ss << a;
    return ss.str();
}

std::string	Response::generateRawResponse(int code, MessageHeaders msg, std::string body){
	if (statusCodeDic[code].empty())
		std::cout << "There is no status available in Dictionnary for code " << intToString(code) << std::endl;
	std::string ret = ("HTTP/1.1 " + intToString(code) + " " + statusCodeDic[code] + "\r\n");
	if (!msg.hasHeader("Content-Length"))
		msg.addHeader("Content-Length", intToString(body.length()));
	else
	{
		if (msg.getHeaderValue("Content-Length") != intToString(body.length()))
			msg.setHeaderValue("Content-Length", intToString(body.length()));
	}
	ret += msg.generateRawMsg();
	ret += body;
	return (ret);
}

std::string	Response::getFormat(std::string & filepath)
{
	std::size_t	formatDelimitor;
	std::string	format;
	formatDelimitor = filepath.find_last_of(".");
	format = filepath.substr(formatDelimitor + 1);
	std::cout << "format is : " << format << std::endl;
	return (format);
}

std::string	Response::getMimeType(std::string & filepath)
{
	std::string	format;
	format = getFormat(filepath);

	for(std::map<std::string, std::string>::iterator it = mimeMap.begin(); it != mimeMap.end(); ++it)
	{
		if (it->first == format)
			return (it->second);
	}
	return ("text/plain");
}

std::vector<char> Response::fileToBinary(std::string file_name1)
{
    std::vector<char> buffer;
    const char* file_name = file_name1.c_str();
    FILE* file_stream = fopen(file_name, "rb");
    size_t file_size;

	(void) file_size;
    if(file_stream != NULL)
    {
        fseek(file_stream, 0, SEEK_END);
        long file_length = ftell(file_stream);
        rewind(file_stream);

        buffer.resize(file_length);

        file_size = fread(&buffer[0], 1, file_length, file_stream);
    }
	return (buffer);
}

std::vector<char>	Response::buildResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret;
	std::string		txtBody;
	std::vector<char> null;

	(void) code;
	msg.addHeader("Date", generateDateHeader());
	msg.addHeader("Content-Type", getMimeType(dir));
	if (getMimeType(dir) == "text/plain" || getMimeType(dir) == "text/html")
	{
		std::cout << "gogo" << std::endl;
		txtBody = check_filename_get_str(dir.c_str());
		if (txtBody.empty())
			return (null);
		data.insert(data.begin(), txtBody.c_str(), txtBody.c_str() + txtBody.size());
	}
	else
	{
		Uri	uri;
		uri.parsingFromString(dir);
		std::string fileDefaultFileName = "inline; filename=";
		fileDefaultFileName += "\"" + uri.getPath().back() + "\"";
		msg.addHeader("Content-Disposition", fileDefaultFileName.c_str());
		data = fileToBinary(dir);
	}
	msg.addHeader("Content-Length", intToString(data.size()));
	ret = ("HTTP/1.1 200 OK\r\n");
	ret += msg.generateRawMsg();
	data.insert(data.begin(), ret.c_str(), ret.c_str()+ ret.size());
	return (data);
}

std::string	Response::generateDateHeader()
{
	std::string weekdays[7] = {"Mon", "Tue", "Wed", "Thr", "Fri", "Sat", "Sun"};
	std::string months[13] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "July", "Aug", "Sep", "Oct", "Nov", "Dec"};
	time_t now = std::time(0);
	tm *ltm = localtime(&now);

	std::string year = intToString(1900 + ltm->tm_year);
	std::string month = months[1 + ltm->tm_mon];
	std::string day = intToString(ltm->tm_mday);
	std::string hour = intToString(ltm->tm_hour);
	std::string minute = intToString(ltm->tm_min);
	std::string sec = intToString(ltm->tm_sec);
	std::string zone = ltm->tm_zone;
	std::string wday = weekdays[ltm->tm_wday];

	return(wday + ", " + day + " " + month + " " + year + " " + hour + ":" + minute + ":" + sec + " " + zone);
}

std::vector<char>	Response::buildErrorResponse(std::string dir, int code)
{
	MessageHeaders	msg;
	std::string		ret;
	std::string		body;
	std::string		filePath;
	std::vector<char> null;

	if (statusCodeDic[code].empty())
		std::cout << "There is no status available in Dictionnary for code " << intToString(code) << std::endl;
	filePath = dir + "/"+ intToString(code) + ".html";
	std::cout << "FilePathName : " << filePath << std::endl;
	body = check_filename_get_str(filePath.c_str());
	if (body.empty())
		return (null);
	ret += "HTTP/1.1 " + intToString(code) + " " + statusCodeDic[code] + "\r\n";
	msg.addHeader("Date", generateDateHeader());
	msg.addHeader("Content-Type", "text/html");
	msg.addHeader("Content-Length", intToString(body.length()));
	ret += msg.generateRawMsg();
	ret += body;
	// make ret. return type to vector<char> and change the send function to see if the whole size of ficher+header has been transfered.
	data.insert(data.end(), ret.c_str(), ret.c_str()+ ret.size());
	return (data);
}

std::vector<char>	Response::getMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) messageEnd;
	// std::string	ret;

	// GET must have empty body, if not, Bad Request.
	if (!request->body.empty())
	{
		statusCode = 400;
		return (buildErrorResponse(server.error_page, 400));
	}
	clientfd = server.clientfd;
	data = buildResponse(server.findMatchingUri(request->target.generateString()), 200);
	statusCode = 200;
	if (data.empty())
	{
		statusCode = 400;
		return (buildErrorResponse(server.error_page, 400));	
	}
	return (data);
}

// std::string	Response::postMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
// 	(void) request;
// 	(void) messageEnd;
// 	(void) request;
// 	(void) statusCode;
// 	(void) server;
// 	std::cout << "In PostMethod\n";
// 	std::string	expectedResponse = (
//      "HTTP/1.1 404 Not Found\r\n"
//      "Content-Length: 35\r\n"
//      "Content-Type: text/plain\r\n"
// 	 "\r\n"
//      "Hello This is Ratatouille server!\r\n"
// 	);
// 	return (expectedResponse);
// }

// std::string	Response::deleteMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
// 	(void) request;
// 	(void) messageEnd;
// 	(void) request;
// 	(void) statusCode;
// 	(void) server;
// 	std::cout << "In DeleteMethod\n";
// 	std::string	expectedResponse = (
//      "HTTP/1.1 404 Not Found\r\n"
//      "Content-Length: 35\r\n"
//      "Content-Type: text/plain\r\n"
// 	 "\r\n"
//      "Hello This is Ratatouille server!\r\n"
// 	);
// 	return (expectedResponse);
// }