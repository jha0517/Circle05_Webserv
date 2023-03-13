/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageHeaders.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 08:03:47 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/09 08:04:49 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESSAGEHEADERS_H
# define MESSAGEHEADERS_H
# include <string>
# include <vector>
# include <iostream>
# include <sstream>

class MessageHeaders
{
public:

	struct	Header{
		std::string	name;
		std::string	value;
	};
	typedef		std::vector<Header> Headers;

	bool		parseFromString(const std::string &rawMsg);
	bool		parseFromString(const std::string &rawMsg, size_t & bodyOffset);
	Headers 	getHeaders() const;
	std::string	getHeaderValue(std::string name) const;
	bool		hasHeader(const std::string &name) const;
	std::string	getBody() const;
	void		setBody(const std::string newBody);
	std::string	generateRawMsg();

	MessageHeaders();
	~MessageHeaders();

private:
	Headers		headers;
	std::string	body;
};

#endif
