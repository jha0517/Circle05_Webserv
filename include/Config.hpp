/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:30:29 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/14 15:58:13 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# define CONFIG_H
# include <string>
# include <vector>
# include "Server.hpp"

class Config
{
private:
	std::vector<Server *> servers;
public:
	Config(/* args */);
	~Config();
	bool	parseFromString(const std::string &rawMsg);
	int		getServerSize();
};
