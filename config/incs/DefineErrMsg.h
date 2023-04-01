/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DefineErrMsg.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhwang <yhwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 01:27:09 by yhwang            #+#    #+#             */
/*   Updated: 2023/04/01 08:43:32 by yhwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_MSG_H
# define DEFINE_MSG_H


/* http block error: 1 ~ 19 */

# define HTTP_BRAKET_OPEN				1
# define HTTP_BRAKET_CLOSE				2
# define HTTP_SEMICOLON					3
# define HTTP_INVALID_KWD				4

# define HTTP_KWD_HTTP					5

# define HTTP_KWD_ROOT					6
# define HTTP_KWD_AUTOINDEX				7
# define HTTP_KWD_DEFAULT_ERROR_PAGE			8

# define HTTP_KWD_ROOT_EXISTS				9
# define HTTP_KWD_AUTOINDEX_EXISTS			10
# define HTTP_KWD_DEFAULT_ERROR_PAGE_EXISTS		11

# define HTTP_KWD_ROOT_MISSED				12
# define HTTP_KWD_AUTOINDEX_MISSED			13
# define HTTP_KWD_DEFAULT_ERROR_PAGE_MISSED		14

/* server block error: 20 ~ 49 */

# define SERVER_BRAKET_OPEN				20
# define SERVER_BRAKET_CLOSE				21
# define SERVER_SEMICOLON				22
# define SERVER_INVALID_KWD				23

# define SERVER_KWD_SERVER				24

# define SERVER_KWD_LISTEN				25
# define SERVER_KWD_HOST				26
# define SERVER_KWD_CLIENT_MAX_BODY_SIZE		27
# define SERVER_KWD_INDEX				28
# define SERVER_KWD_ALLOW_METHODS			29

# define SERVER_KWD_LISTEN_EXISTS			25
# define SERVER_KWD_HOST_EXISTS				26
# define SERVER_KWD_CLIENT_MAX_BODY_SIZE_EXISTS		27
# define SERVER_KWD_INDEX_EXISTS			28
# define SERVER_KWD_ALLOW_METHODS_EXISTS		29

# define SERVER_KWD_LISTEN_MISSED			30
# define SERVER_KWD_HOST_MISSED				31
# define SERVER_KWD_CLIENT_MAX_BODY_SIZE_MISSED		32
# define SERVER_KWD_INDEX_MISSED			33
# define SERVER_KWD_ALLOW_METHODS_MISSED		34

/* location block error: 50 ~ 80 */

# define LOCATION_BRAKET_OPEN				50
# define LOCATION_BRAKET_CLOSE				51
# define LOCATION_SEMICOLON				52
# define LOCATION_INVALID_KWD				53

# define LOCATION_KWD_LOCATION				54

# define LOCATION_KWD_REDIRECTION_PATH			55
# define LOCATION_KWD_RETURN				56
# define LOCATION_KWD_RETURN_VALUE			57
# define LOCATION_KWD_CGI_BIN				58
# define LOCATION_KWD_CGI_BIN_ROOT			59
# define LOCATION_KWD_CGI_BIN_CGI_PATH			60
# define LOCATION_KWD_CGI_BIN_CGI_EXTENTION		61

# define LOCATION_KWD_RETURN_EXISTS			62
# define LOCATION_KWD_CGI_BIN_EXISTS			63
# define LOCATION_KWD_CGI_BIN_ROOT_EXISTS		64
# define LOCATION_KWD_CGI_BIN_CGI_PATH_EXISTS		65	
# define LOCATION_KWD_CGI_BIN_CGI_EXTENTION_EXISTS	66

# define LOCATION_KWD_RETURN_MISSED			67
# define LOCATION_KWD_CGI_BIN_MISSED			68
# define LOCATION_KWD_CGI_BIN_ROOT_MISSED		69
# define LOCATION_KWD_CGI_BIN_CGI_PATH_MISSED		70	
# define LOCATION_KWD_CGI_BIN_CGI_EXTENTION_MISSED	71

#endif
