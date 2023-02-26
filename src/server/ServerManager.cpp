
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
    // cd /etc/nginx/sites-available/default 
    // 
	// if (foundServerBlock)
		// config.push_back();
}


void	ServerManager::printLog(){
	std::cout << "Number of server block : " << std::endl;
	std::cout << "Server Block is " << std::endl;
	std::cout << "Server Name is " << std::endl;
	std::cout << "Location Block is " << std::endl;
}

void	ServerManager::runServer(char *ip){
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    (void) valread;

    std::string hello = "Hello from server\n";
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( atoi(ip) );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    // while(1)
    // {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        printf("%s\n",buffer );
		printf("pid : %ld\n", (long)getpid());
        write(new_socket , hello.c_str() , strlen(hello.c_str()));
        printf("------------------Hello message sent-------------------\n");
        close(new_socket);
        close(server_fd);
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
