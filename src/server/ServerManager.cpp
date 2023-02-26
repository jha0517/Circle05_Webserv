
#include "../../include/webserv.hpp"


ServerManager::ServerManager(/* args */)
{
}

ServerManager::~ServerManager()
{
}

void	ServerManager::setConfiguration(char *configFile, char **env){
	(void) env;
	(void) configFile;
	//parsing.

	// if (foundServerBlock)
		// config.push_back();
}


void	ServerManager::printLog(){
	std::cout << "Number of server block : " << std::endl;
	std::cout << "Server Block is " << std::endl;
	std::cout << "Server Name is " << std::endl;
	std::cout << "Location Block is " << std::endl;
}


void	ServerManager::createServer(){
    // std::string	ip = "127.0.0.1";
    // // Creating socket file descriptor
    // if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    // {
    //     perror("In socket");
    //     exit(EXIT_FAILURE);
    // }
    
	// // ip = config.getIp;
    // address.sin_family = AF_INET;
    // address.sin_addr.s_addr = INADDR_ANY;
    // address.sin_port = htons(atoi(ip.c_str()));
    
    // memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    // if (bind(serverFd, (struct sockaddr *)&address, sizeof(address))<0)
    // {
    //     perror("In bind");
    //     exit(EXIT_FAILURE);
    // }
    // if (listen(serverFd, 10) < 0)
    // {
    //     perror("In listen");
    //     exit(EXIT_FAILURE);
    // }
}

void	ServerManager::runServer(){
    // int new_socket; long valread;
    // std::string hello = "Hello from server\n";
    // int addrlen = sizeof(address);
	// //TO DO : Select or Poll or epoll
	// //TO DO : Multi client connection
	// //TO DO : CGI
	// (void) valread;
    // while(1)
    // {
    //     printf("\n+++++++ Waiting for new connection ++++++++\n\n");
    //     if ((new_socket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
    //     {
    //         perror("In accept");
    //         exit(EXIT_FAILURE);
    //     }
        
	// 	char buffer[30000] = {0};
	// 	valread = read( new_socket , buffer, 30000);
	// 	try {
	// 		// request = getValidRequest(buffer);
	// 		// response = createResponse(request);
	// 		printf("Debug : %s\n",buffer );
	// 		printf("pid : %ld\n", (long)getpid());
    //     	write(new_socket , hello.c_str() , strlen(hello.c_str()));
	// 	}
	// 	catch(std::exception& e){
	// 		std::cout <<  e.what() << std::endl;
	// 	}
    //     close(new_socket);
    // }
}

Request		*ServerManager::getValidRequest(char *buffer){
	Request *ret = NULL;
	(void) buffer;
	return (ret);
}
Response	*ServerManager::createResponse(Request *request){
	Response *ret = NULL;
	(void) request;
	return (ret);
}
