/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefineErrMsg.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 01:27:09 by yhwang            #+#    #+#             */
/*   Updated: 2023/03/23 02:43:52 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_MSG_H
# define DEFINE_MSG_H


/* http block error: 1 ~ 19 */

# define HTTP_BRAKET_OPEN			1
# define HTTP_BRAKET_CLOSE			2
# define HTTP_SEMICOLON				3
# define HTTP_INVALID_KWD			4

# define HTTP_KWD_HTTP				5

# define HTTP_KWD_ROOT				6
# define HTTP_KWD_AUTOINDEX			7
# define HTTP_KWD_DEFAULT_ERROR_PAGE		8

# define HTTP_KWD_ROOT_MISSED			9
# define HTTP_KWD_AUTOINDEX_MISSED		10
# define HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED	11

/* server block error: 20 ~ 49 */

# define SERVER_BRAKET_OPEN			20
# define SERVER_BRAKET_CLOSE			21
# define SERVER_SEMICOLON			22
# define SERVER_INVALID_KWD			23

# define SERVER_KWD_SERVER			24

# define SERVER_KWD_LISTEN			25
# define SERVER_KWD_HOST			26
# define SERVER_KWD_CLIENT_MAX_BODY_SIZE	27
# define SERVER_KWD_INDEX			28
# define SERVER_KWD_ALLOW_METHODS		29

# define SERVER_KWD_LISTEN_MISSED		30
# define SERVER_KWD_HOST_MISSED			31
# define SERVER_KWD_CLIENT_MAX_BODY_SIZE_MISSED	32
# define SERVER_KWD_INDEX_MISSED		33
# define SERVER_KWD_ALLOW_METHODS_MISSED	34

#endif
