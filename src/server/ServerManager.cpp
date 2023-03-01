
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

std::string	checkFileAndGetContent(char *filename)
{
	std::string		src;
	std::string		rawRequest;
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

	str = checkFileAndGetContent(configFile);
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
    (void) env;
}


void	ServerManager::printLog(){
}

void	ServerManager::runServer(unsigned int port){
    int server_fd, clientSocket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    (void) valread;
    
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
        if ((clientSocket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char rawRequest[3000] = {0};
        valread = read( clientSocket , rawRequest, 3000);
        printf("%s\n",rawRequest );
        // request.parsing(rawRequest);

        response.send(clientSocket);
        // if (request.getMethod() == GET)
        //     response.templateGet(clientSocket);
        // else if (request.getMethod() == POST)
        //     response.templatePost(clientSocket);
        // else if (request.getMethod() == DELETE)
        //     response.templateDelete(clientSocket);
        close(clientSocket);
    }
    close(server_fd);
}
