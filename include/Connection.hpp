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

typedef void(*DataReceivedDelegate)(std::vector<unsigned char>);
typedef void(*BrokenDelegate)();

class Connection
{
public:

	Connection(int socketfd);
	~Connection();

	// //local site want to receive some thing, it will use setDataReceivedDelegate,and use presumably dataReceivedDelegate given by connection.?.
	// virtual void	setDataReceivedDelegate(DataReceivedDelegate dataReceivedDelegate) = 0;
	// //local site want to send data, it will use sendData.
	// virtual void	sendData(std::vector<unsigned char> data) = 0; // unsigned char 0-255, == uchar
	// virtual void	setBrokenDelegate(BrokenDelegate brokenDelegate) = 0;
	// virtual void	breakConnection(bool clean);

	//local site want to receive some thing, it will use setDataReceivedDelegate,and use presumably dataReceivedDelegate given by connection.?.
	void	setDataReceivedDelegate(DataReceivedDelegate dataReceivedDelegate);
	//local site want to send data, it will use sendData.
	void	sendData(std::vector<unsigned char> data); // unsigned char 0-255, == uchar
	void	setBrokenDelegate(BrokenDelegate brokenDelegate);
	void	breakConnection(bool clean);

	std::vector<unsigned char>	dataReceived;
	BrokenDelegate				brokenDelegate;
	DataReceivedDelegate	dataReceivedDelegate;

private:
	Connection();
	int	socketfd;
};

#endif
