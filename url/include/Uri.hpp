
#ifndef URI_H
# define URI_H
# include <string>
# include <vector>


class Uri
{
private:
	bool		existPath;
	bool		existPort;
	// bool		isRelativeReference;
	uint16_t	port;
	std::string	scheme;
	std::string	host;
	std::vector<std::string> path;
	std::string	splitchar;

public:
	Uri();
	~Uri();
	bool						ParsingFromString(const std::string & uriString);
	std::string					getScheme() const;
	std::string					getHost() const;
	std::vector<std::string>	getPath();
	void						setSplitChar(std::string newchar);
	bool						hasPath() const;
	bool						hasPort() const;
	// bool						isRelativeReference() const;
	uint16_t					getPort() const;
};

#endif 
