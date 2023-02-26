
#include "webserv.hpp"

int	main(int ac, char **av, char **env)
{
    ServerManager manager;

	manager.printLog();
	if (ac != 2)
	{
		std::cout << "Need 1 config file" << std::endl;
		return (1);
	}
	try{
		manager.setConfiguration(av[1], env);
	}
	catch(std::exception& e){
		std::cout << e.what() << std::endl;
		return (2);
	}
	manager.runServer(av[1]);
    return 0;
}