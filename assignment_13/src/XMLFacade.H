#ifndef XMLFACADE_H
#define XMLFACADE_H

#include <string>
#include <vector>

// Facade Pattern: Facade
class XMLFacade
{
public:
	XMLFacade();
	~XMLFacade();

	void	tokenize(const std::vector<std::string> & files);
	void	serialize(const std::string & prettyOut, const std::string & minimalOut);
	void	validate(const std::string & prettyOut);
	void	interpret(const std::string & inputFile);
};

#endif // XMLFACADE_H
