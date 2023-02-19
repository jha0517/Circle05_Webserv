
#include "include/webserv.hpp"

int	main()
{
	// std::cout << "Starting.." << std::endl;
	// std::cout << "Binding Socket.." << std::endl;
	// BindingSocket bs(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY);
	// std::cout << "Listening Socket..." << std::endl;
	// ListeningSocket ls(AF_INET, SOCK_STREAM, 0, 80, INADDR_ANY, 10);
	// std::cout << "Success..." << std::endl;
	TestServer	t;
	t.launch();
}