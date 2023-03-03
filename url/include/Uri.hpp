
#ifndef URI_H
# define URI_H
# include <string>
# include <vector>


class Uri
{
private:
	std::string	scheme;
	std::string	host;
	std::vector<std::string> path;
	std::string	splitchar;

public:
	Uri();
	~Uri();
	bool	ParsingFromString(const std::string & uriString);
	std::string	getScheme() const;
	std::string	getHost() const;
	std::vector<std::string> getPath();
	void	setSplitChar(std::string newchar);
};

#endif 
