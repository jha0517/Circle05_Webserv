/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acostin <acostin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:56:00 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/03 02:17:08 by acostin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

int	main(int argc, char **argv)
{
	/* error check: argument */
	if (!(argc == 1 || argc == 2))
	{
		std::cerr << RED << "Error: Argument error" << BLACK << std::endl
			<< "(command: " << CYAN << "./parse" << BLACK << " or "
			<< CYAN << "./parse config_file_name" << BLACK ")" << std::endl;
		return (1);
	}

	try
	{
		if (argc == 1)
			Parse	p("conf_files/default.conf");
		else
			Parse	p(argv[1]);
	}
	catch(std::string err_msg)
	{
		std::cerr << err_msg << std::endl;
	}

	std::cout << "\nparsing done" << std::endl;
	
	return (0);
}
