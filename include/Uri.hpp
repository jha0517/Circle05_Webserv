/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Uri.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 00:19:46 by hyunah            #+#    #+#             */
/*   Updated: 2023/04/02 20:26:26 by hyunah           ###   ########.fr       */
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
	bool			existPath;
	bool			existPort;
	unsigned short	port; // uint16.
	std::string		parseScheme(std::string uriString);
	void			parsePath(std::string & pathString);
	std::string		findQueryFragment(std::string & rest, std::string & queryAndOrFrag);
	void			parseQueryFragment(std::string & queryAndOrFrag);
	bool			parseValidPort(std::string &pathString, int portDelimeter, int authorityEnd);
	void			parseFragment(std::string & queryAndOrFrag);
	std::string		scheme;
	std::string		host;
	std::string		splitchar;
	std::string		fragment;
	std::string		query;
	std::vector<std::string> path;

public:
	Uri();
	Uri(Uri const & src);
	Uri &operator=(Uri const & rhs);
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
	std::string					constructPath();
	std::vector<std::string>	getPath();
	unsigned short				getPort() const;

	void						setSplitChar(const std::string & newchar);
	void						setScheme(const std::string & newScheme);
	void						setHost(const std::string & newHost);
	void						setQuery(const std::string & newQuery);
	Uri & 						operator=(const Uri &rhs);
	bool 						operator==(Uri const &rhs) const;
};


std::ostream & operator<<(std::ostream & o, Uri & rhs);

#endif 
