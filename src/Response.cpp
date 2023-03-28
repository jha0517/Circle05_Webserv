/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:13:24 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/28 18:08:39 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Response.hpp"
#include <sys/wait.h>
#include <algorithm>

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

	(void)file_size;
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

std::size_t	vecFind2(std::vector<char> rawRequest, std::string str)
{
	size_t	i = 0;
	size_t	v = 0;

	for (std::vector<char>::iterator it = rawRequest.begin(); it != rawRequest.end(); ++it)
	{
		i = 0;
		if (*it == str[i])
		{
			while (*(it + i) == str[i])
			{
				// printf("Comparing vector char %c with str %c\n", *(it + 1), str[i]);
				// printf("i is %li, str.length is %li, returning %li\n", i, str.length()-1, v);
				if (i == str.length() - 1)
					return (v);
				i++;
			}
		}
		v++;
	}
	return (std::string::npos);
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

std::vector<char>	Response::buildResponseForCgi(std::vector<char> data, int code)
{
	MessageHeaders	msg;
	std::string		ret;
	std::string		txtBody;
	std::vector<char> null;

	(void) code;
	std::string str(data.begin(), data.end());
	msg.addHeader("Date", generateDateHeader());
	std::string bodyDeliminator = "\r\n\r\n";
	std::size_t i = vecFind2(data, bodyDeliminator);
	std::string header(data.begin(), data.begin() + i + 2);
	std::cout << "header : " << header << "\n";
	std::cout << "Body deliminator :  " << i << "\n";
	data.erase(data.begin(), data.begin() + i + 4);
	msg.addHeader("Content-Length", intToString(data.size()));
	ret = ("HTTP/1.1 200 OK\r\n");
	ret += header;
	ret += msg.generateRawMsg();
	data.insert(data.begin(), ret.c_str(), ret.c_str()+ ret.size());
	return (data);
}

std::vector<char>	Response::getMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) messageEnd;

	// GET must have empty body, if not, Bad Request.
	if (!request->body.empty())
	{
		statusCode = 400;
		return (buildErrorResponse(server.error_page, 400));
	}
	if (!request->target.getQuery().empty())
	{
		std::string pathphp = "/home/hyunah/Documents/webserv/data/query.php";
		std::string arg1 = "php-cgi";
		char	*path[] = {strdup(arg1.c_str()), strdup(pathphp.c_str()), NULL};
		char	*newEnv[] = {strdup(request->target.getQuery().c_str()), NULL};
		std::vector<char>	data;

		int pipefd[2];
		if (pipe(pipefd) == -1)
		{
			printf("Error in opening pipe\n");
		}

		int id = fork();
		if (id == 0)
		{
			close(pipefd[0]);    // close reading end in the child
			dup2(pipefd[1], 1);  // send stdout to the pipe
			// dup2(pipefd[1], 2);  // send stderr to the pipe
			close(pipefd[1]);    // this descriptor is no longer needed
			execve("/usr/bin/php-cgi", path, newEnv);
			// exec(...);
		}
		else
		{
			// parent

			char buffer[1];

			close(pipefd[1]);  // close the write end of the pipe in the parent

			int n;
			while ((n = read(pipefd[0], buffer, 1)) > 0)
			{
				if (n < 0)
					printf("read failed\n");
				data.insert(data.end(), buffer, buffer + n);
				bzero(buffer, sizeof(buffer));
			}
			printf("Got from child Process\n");
			for (std::vector<char>::iterator it = data.begin(); it != data.end(); ++it)
			{
				std::cout << *it;
			}
			std::cout << std::endl;
		}
		wait(NULL);
		// printf("End php function\n");
		data = buildResponseForCgi(data, 200);
		return (data);
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

void makeArray(char **env)
{
	int i = -1;
	while (env[++i])
		printf("%s\n",env[i]);
	printf("total %i\n", i);
	// std::string newenv1 = "TESTHYUNAH=HYUNAH";
	// char	*newEnv[] = {strdup(newenv1.c_str()), NULL};

	return ;
}

void	addEnv(std::vector<std::string> &env, std::string key, std::string value)
{
	env.push_back(key + "=" + value);
}

std::vector<char>	Response::postMethod(Server &server, Request *request, std::size_t messageEnd, int & statusCode){
	(void) request;
	(void) messageEnd;
	(void) request;
	(void) statusCode;
	(void) server;
	std::cout << "In PostMethod\n";
	// think how we gonna use cgi to post file.

	// Replace to config path later.
	std::string pathphp = "/home/hyunah/Documents/webserv/data/upload.php";
	std::string arg1 = "php-cgi";
	char	*path[] = {strdup(arg1.c_str()), strdup(pathphp.c_str()), NULL};


	int id = fork();

	if (id == 0)
	{
		std::vector<std::string>	env;
		std::vector<char>			filebody;
		addEnv(env, "AUTH_TYPE", "Basic");
		// addEnv(env, "CONTENT_LENGTH", request->headers.getHeaderValue("Content-Length"));
		addEnv(env, "CONTENT_TYPE", request->headers.getHeaderValue("Content-Type"));
		addEnv(env, "GATEWAY_INTERFACE", "CGI/1.1");
		addEnv(env, "SCRIPT_NAME", "upload.php");
		addEnv(env, "SCRIPT_FILENAME", pathphp);
		addEnv(env, "REDIRECT_STATUS", "200");
		addEnv(env, "QUERY_STRING", request->target.getQuery());
		addEnv(env, "REMOTE_ADDR", server.host + ":" + intToString(server.port));
		addEnv(env, "SERVER_NAME", server.host);
		addEnv(env, "SERVER_PORT", intToString(server.port));
		addEnv(env, "REQUEST_METHOD", request->method);
		addEnv(env, "REQUEST_URI", request->target.generateString());
		addEnv(env, "SERVER_PROTOCOL", "HTTP/1.1");
		
		// find body deliminator
		filebody = request->body;
		std::string deliminator = "boundary=";
		std::size_t b = request->headers.getHeaderValue("Content-Type").find(deliminator);
		std::string nextline = "\r\n";
		std::string bodyDeliminator = request->headers.getHeaderValue("Content-Type").substr(b + deliminator.length());
		// std::cout << "Body deliminator : <" << bodyDeliminator << ">\n";
		std::size_t a = vecFind2(request->body, bodyDeliminator);

		// erase start boundary
		filebody.erase(filebody.begin(), filebody.begin() + a + bodyDeliminator.length() + nextline.length());
		a = vecFind2(filebody, bodyDeliminator);
		filebody.erase(filebody.begin(), filebody.begin() + a + bodyDeliminator.length() + nextline.length());

		// erase end boundary		
		a = vecFind2(filebody, bodyDeliminator);
		filebody.erase(filebody.begin() + a - (nextline.length() * 2), filebody.end());
		
		// split fileinfo and body
		std::vector<char>	infoFile;
		a = vecFind2(filebody, "\r\n\r\n");
		infoFile.insert(infoFile.begin(), filebody.begin(), filebody.begin() + a);
		filebody.erase(filebody.begin(), filebody.begin() + a + 4);

		// std::cout << std::endl << "InfoFile body" << std::endl;
		// for	(std::vector<char>::iterator it = infoFile.begin(); it != infoFile.end(); ++it)
			// std::cout << *it;
		// std::cout << std::endl << "InfoFile body END" << std::endl;

		std::cout << std::endl << "File body (size "<< filebody.size() << ")" << std::endl;
		// for	(std::vector<char>::iterator it = filebody.begin(); it != filebody.end(); ++it)
			// std::cout << *it;
		// std::cout << "File body END" << std::endl;
		
		// Put variable, filename in env.
		std::string infoFileHeader;
		MessageHeaders msg;

		infoFileHeader.insert(infoFileHeader.begin(), infoFile.begin(), infoFile.end());
		msg.parseFromString(infoFileHeader);
		std::string rest = msg.getHeaderValue("Content-Disposition");
		std::string type = msg.getHeaderValue("Content-Type");
		size_t j;
		size_t k;
		std::string value;
		std::string filename;
		
		while ((j = rest.find(" ")) != std::string::npos)
		{
			value = rest.substr(0, j);
			if ((k = value.find("=")) != std::string::npos)
			{
				size_t l = value.find("\"", k + 2);
				// std::cout <<value.substr(0, k) << " " << value.substr(k + 2, value.size() - (k + 2) - (value.size() - l)) << std::endl;
				addEnv(env, value.substr(0, k), value.substr(k + 2, value.size() - (k + 2) - (value.size() - l)));
			}
			rest.erase(rest.begin(), rest.begin() + j + 1);
		}
		if ((k = rest.find("=")) != std::string::npos)
		{
			size_t l = rest.find("\"", k + 2);
			filename = rest.substr(k + 2, value.size() - (k + 2) - (value.size() - l));
			addEnv(env, rest.substr(0, k), filename);
		}
		std::string pathTmpFile = "/home/hyunah/Documents/webserv/data/upload";
		addEnv(env, "FILE_TEMPLOC", pathTmpFile);

		//upload in server
		std::string patch = pathTmpFile + "/" + filename;
		std::ofstream myFile(patch.c_str());
		for (std::vector<char>::iterator it = filebody.begin(); it != filebody.end(); ++it)
			myFile << *it;
		myFile.close();
		addEnv(env, "UPLOAD_ERROR", intToString(0));

		char	**newEnv = (char **)calloc(sizeof(char *), env.size() + 1);
		int i = 0;
		for (std::vector<std::string>::iterator it = env.begin(); it != env.end(); ++it)
		{
			newEnv[i] = strdup(it->c_str());
			std::cout << i << ". " << it->c_str() << std::endl;
			i++;
		}

		// execute
		execve("/usr/bin/php-cgi", path, newEnv);
		perror("execve");
	}
	wait(NULL);
	printf("End php function\n");
	statusCode = 404;
	return (buildErrorResponse(server.error_page, 404));
}

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