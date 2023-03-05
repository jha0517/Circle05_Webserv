/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:19:46 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/05 14:26:47 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_H
# define URI_H
# include <string>
# include <vector>

//TO DO : 
// ip address as a host

class Uri
{
private:
	bool		existPath;
	bool		existPort;
	uint16_t	port;
	std::string	scheme;
	std::string	fragment;
	std::string	query;
	std::string	host;
	std::vector<std::string> path;
	std::string	splitchar;

public:
	Uri();
	~Uri();
	bool						ParsingFromString(const std::string & uriString);
	std::string					generateString();
	bool						hasPath() const;
	bool						hasPort() const;
	bool						hasRelativeReference() const;
	bool						ContainsRelativePath() const;

	std::string					getScheme() const;
	std::string					getFragement() const;
	std::string					getQuery() const;
	std::string					getHost() const;
	std::vector<std::string>	getPath();
	uint16_t					getPort() const;

	void						setSplitChar(const std::string & newchar);
	void						setScheme(const std::string & newScheme);
	void						setHost(const std::string & newHost);
	void						setQuery(const std::string & newQuery);
};

#endif 
