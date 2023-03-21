/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:56:00 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/18 20:32:59 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/Parse.hpp"

int	main(int argc, char **argv)
{
	/* error check: argument */
	if (!(argc == 1 || argc == 2))
	{
		std::cerr << "Error: Argument error" << std::endl;
		return (1);
	}

	try
	{
		if (argc == 1)
			Parse	p("conf_files/default.conf");
		else
			Parse	p(argv[1]);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	
	
	
	std::cout << "\nparsing done" << std::endl;
	
	return (0);
}
