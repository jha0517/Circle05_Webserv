
#include "webserv.hpp"

int	main(int ac, char **av, char **env)
{
    ServerManager manager;

	// manager.printLog();
	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (1);
	}
	try{
		manager.setConfiguration(av[1], env);
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
		return (2);
	}
	manager.runServer(manager.configList.front()->getPort());
    return 0;
}