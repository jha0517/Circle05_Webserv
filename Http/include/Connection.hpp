/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connection.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyunah <hyunah@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 11:25:04 by hyunah            #+#    #+#             */
/*   Updated: 2023/03/06 11:25:53 by hyunah           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONNECTION_H
# define CONNECTION_H
# include <string>
# include <vector>

class Connection
{
public:
	Connection();
	~Connection();
	// virtual void	SetDataReceivedDelegate(std::vector<uint8_t> dataReceivedDelegate);
	// virtual void	SetBrokenDelegate(void *brokenDelegate);
	// virtual void	breakConnection(bool clean);
	// virtual void	sendData(std::vector<uint8_t> data); // uint_8 0-255, == uchar

private:
};

#endif
