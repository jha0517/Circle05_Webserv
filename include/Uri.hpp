/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:19:46 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/13 17:30:35 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef URI_H
# define URI_H
# include <string>
# include <vector>
# include <stdlib.h>

//TO DO : 
// ip address as a host

class Uri
{
private:
	bool		existPath;
	bool		existPort;
	unsigned short	port;
	std::string	scheme;
	std::string	host;
	std::string	splitchar;
	std::string	fragment;
	std::string	query;
	std::vector<std::string> path;

public:
	Uri();
	~Uri();
	bool						parsingFromString(const std::string & uriString);
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
	unsigned short					getPort() const;

	void						setSplitChar(const std::string & newchar);
	void						setScheme(const std::string & newScheme);
	void						setHost(const std::string & newHost);
	void						setQuery(const std::string & newQuery);
	Uri & 						operator=(const Uri &rhs);
	bool 						operator==(Uri const &rhs) const;
};

#endif 
