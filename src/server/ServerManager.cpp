
#include "../../include/webserv.hpp"

ServerManager::errorMsg::errorMsg(const char *message) : message(message) {}

const char *ServerManager::errorMsg::what() const throw(){ return message; }

ServerManager::ServerManager()
{
}

ServerManager::~ServerManager()
{
}

bool	checkBalancedParantheses(std::string s)
{
	std::stack<char>par;

	for (unsigned i = 0; i < s.size(); i++)
	{
		if (s[i] == '{')
			par.push(s[i]);
		else if (s[i] == '}')
		{
			if (s.empty() || par.top() != '{')
				return (false);
			else
				par.pop();
		}
	}
	return (par.empty() ? true : false);
}

std::string	checkFilenameGetContent(char *filename)
{
	std::string		src;
	std::string		buffer;
	std::ifstream	ifs;
	char	c;
	
	ifs.open(filename);
	if (ifs.fail())
	{
		std::cerr << "Error : File opening failed." << std::endl;
		return (NULL);
	}
	while (ifs.get(c))
		src+= c;
	ifs.close();
	return (src);
}

bool	formatcheck(char *configFile)
{
	std::string	str;

	str = checkFilenameGetContent(configFile);
	if (!checkBalancedParantheses(str))
		throw ServerManager::errorMsg("Error : Config file Parantheses not balanced\n");
	return (true);
}

unsigned int    foundServerContext(char *configFile)
{
    unsigned int len;
    len = 0;
    (void) configFile;
    return (len);
}

void	ServerManager::setConfiguration(char *configFile, char **env){
	formatcheck(configFile);
    Config  *c = new Config;

	configList.push_back(c);
    (void) env;
	// std::list<std::string> keyword = {"listen", "server_name", "root", "error_page", "client_body_buffer_size"};

	// for (unsigned i = 0; i < foundServerContext(configFile); i++)
	// {
    //     configList.front()->update();
	// }
	// std::cout << configFile << std::endl;
}


void	ServerManager::printLog(){
}

void	ServerManager::runServer(unsigned int port){
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
    address.sin_port = htons(port);
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        if (port <= 1024)
            std::cout << "Ports below 1024 are considered privileged can only be bound to with an equally privileged user. Run as Sudo or use port over 1024."<< std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char buffer[3000] = {0};
        valread = read( new_socket , buffer, 3000);
        // printf("%s\n",buffer );
		// printf("pid : %ld\n", (long)getpid());
        response.send(new_socket);
        close(new_socket);
    }
    close(server_fd);
}

Request		*ServerManager::getValidRequest(char *buffer){
	Request *ret = NULL;
	(void) buffer;
	return (ret);
}
// Response	*ServerManager::createResponse(Request *request){
// 	Response *ret = NULL;
// 	(void) request;
// 	return (ret);
// }
