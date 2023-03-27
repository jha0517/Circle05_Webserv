/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ParseUtils.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 04:20:47 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:43:35 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/ParseUtils.h"

int	StringCheck(std::string str)
{
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (!(str[i] == ' ' || str[i] == '\t'))
			return (1);
	}
	return (0);
}

int	StringCheck(std::string str, char c)
{
	for (int i = 0; i < (int)str.length(); i++)
	{
		if (!(str[i] == ' ' || str[i] == '\t' || str[i] == c))
			return (1);
	}
	return (0);
}

int	SemicolonCheck(std::string str)
{
	int	flag = 0;

	for (int i = 0; i < (int)str.length(); i++)
		if (str[i] == ';')
			flag++;
	if (flag != 1)
		return (1);
	if (!(str[str.length() - 1] == ';'))
		return (1);
	return (0);
}

static std::string	ReplaceLine(std::string line, std::string s1, std::string s2)
{
	std::string	new_line = "";
	int		pos = 0;
	int		find = 0;

	while (1)
	{
		find = line.find(s1, pos);
		if (find == -1)
		{
			new_line += line.substr(pos, std::string::npos);
			break ;
		}
		new_line += line.substr(pos, find - pos);
		new_line += s2;
		pos += (find - pos + s1.length());
	}
	return (new_line);
}

int	TokenCount(int n, std::string line, std::string *token)
{
	int		i = 0;

	line = ReplaceLine(line, "\t", " ");
	std::stringstream	ss(line);
	while (!ss.eof())
	{
		getline(ss, token[i], ' ');
		if (token[i] == "")
			continue ;
		i++;
	}
	if (i != n)
		return (1);
	return (0);
}

int	TokenCount(std::string line, std::string *token)
{
	int		i = 0;

	line = ReplaceLine(line, "\t", " ");
	std::stringstream	ss(line);
	while (!ss.eof())
	{
		getline(ss, token[i], ' ');
		if (token[i] == "")
			continue ;
		i++;
	}
	return (i);
}

std::string	ErrMsg(std::string file_name, int err_number, std::string line, int i)
{
	std::string	msg = file_name;

	msg.append(":");

	std::stringstream	ss;
	ss << i;
	msg.append(ss.str());

	msg.append(": ");
	msg.append(RED);
	msg.append("error: ");
	msg.append(BLACK);

	if (1 <= err_number && err_number <= 19)
	{
		msg.append("http block: ");
		if (err_number == HTTP_BRAKET_OPEN)
			msg.append("'{' is missed or not opened properly\n");
		else if (err_number == HTTP_BRAKET_CLOSE)
			msg.append("'}' is missed or not closed properly\n");
		else if (err_number == HTTP_SEMICOLON)
			msg.append("';' is missed or used multiple time\n");
		else if (err_number == HTTP_INVALID_KWD)
			msg.append("found invalid character(s)\n");
		else if (err_number == HTTP_KWD_HTTP)
			msg.append("keyword http\n");
		else if (err_number == HTTP_KWD_ROOT)
			msg.append("keyword root\n");
		else if (err_number == HTTP_KWD_AUTOINDEX)
			msg.append("keyword autoindex\n");
		else if (err_number == HTTP_KWD_DEFAULT_ERROR_PAGE)
			msg.append("keyword default_error_page\n");
		//else if (err_number == HTTP_KWD_ROOT_MISSED)
		// 	msg.append("keyword root is missed\n");
		// else if (err_number == HTTP_KWD_AUTOINDEX_MISSED)
		// 	msg.append("keyword autoindex is missed\n");
		// else if (err_number == HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED)
		// 	msg.append("keyword default_error_page is missed\n");
	}
	else if (20 <= err_number && err_number <= 49)
	{
		msg.append("server block: ");
		if (err_number == SERVER_BRAKET_OPEN)
			msg.append("'{' is missed or not opened properly\n");
		else if (err_number == SERVER_BRAKET_CLOSE)
			msg.append("'}' is missed or not closed properly\n");
		else if (err_number == SERVER_SEMICOLON)
			msg.append("';' is missed or used multiple time\n");
		else if (err_number == SERVER_INVALID_KWD)
			msg.append("found invalid character(s)\n");
		else if (err_number == SERVER_KWD_SERVER)
			msg.append("keyword server\n");
		else if (err_number == SERVER_KWD_LISTEN)
			msg.append("keyword listen\n");
		else if (err_number == SERVER_KWD_HOST)
			msg.append("keyword host\n");
		else if (err_number == SERVER_KWD_CLIENT_MAX_BODY_SIZE)
			msg.append("keyword client_max_body_size\n");
		else if (err_number == SERVER_KWD_INDEX)
			msg.append("keyword index\n");
		else if (err_number == SERVER_KWD_ALLOW_METHODS)
			msg.append("keyword allow_methods\n");
	}
	
	if (i < 10)
		msg.append("   ");
	else if (i < 100)
		msg.append("  ");
	else
		msg.append(" ");

	msg.append(ss.str());
	msg.append(" | ");
	
	msg.append(line);
	return (msg);
}

std::string	ErrMsg(std::string file_name, int err_number)
{
	std::string	msg = file_name;

	msg.append(": ");
	msg.append(RED);
	msg.append("error: ");
	msg.append(BLACK);

	if (1 <= err_number && err_number <= 19)
	{
		msg.append("http block: ");
		if (err_number == HTTP_BRAKET_OPEN)
			msg.append("'{' is missed or not opened properly\n");
		else if (err_number == HTTP_KWD_ROOT_MISSED)
			msg.append("keyword root is missed\n");
		else if (err_number == HTTP_KWD_AUTOINDEX_MISSED)
			msg.append("keyword autoindex is missed\n");
		else if (err_number == HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED)
			msg.append("keyword default_error_page is missed\n");
	}
	else if (20 <= err_number && err_number <= 49)
	{
		msg.append("server block: ");
		if (err_number == SERVER_BRAKET_OPEN)
			msg.append("'{' is missed or not opened properly\n");
		else if (err_number == SERVER_KWD_LISTEN_MISSED)
			msg.append("keyword listen is missed\n");
		else if (err_number == SERVER_KWD_HOST_MISSED)
			msg.append("keyword host is missed\n");
		else if (err_number == SERVER_KWD_CLIENT_MAX_BODY_SIZE_MISSED)
			msg.append("keyword client_max_body_size is missed\n");
		else if (err_number == SERVER_KWD_INDEX_MISSED)
			msg.append("keyword index is missed\n");
		else if (err_number == SERVER_KWD_ALLOW_METHODS_MISSED)
			msg.append("keyword allow_methods is missed\n");
	}
	return (msg);
}
