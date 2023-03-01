
#include "webserv.hpp"
// enum Method2 { GET2, POST, DELETE};

void	signalHandler(int signum)
{
	std::cout << "\nLeaving the server...Bye!" << std::endl;
	exit(signum);
}

int	main(int ac, char **av, char **env)
{
    ServerManager manager;
	signal(SIGINT, signalHandler);

	(void) av;
	(void) env;
	if (ac != 2)
	{
		std::cerr << "Need 1 config file OR default path." << std::endl;
		return (1);
	}
	try{
		// manager.setConfiguration(av[1], env);
	}
	catch(std::exception& e){
		std::cerr << e.what() << std::endl;
		return (2);
	}
	manager.runServer(8080);
    return 0;
}