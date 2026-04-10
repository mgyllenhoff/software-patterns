#ifndef XMLLOADER_H
#define XMLLOADER_H

#include "Document.H"

// Layer 3: Application Logic Layer
// Command Pattern: Receiver
class XMLLoader
{
public:
	XMLLoader(void)		{}
	virtual ~XMLLoader()	{}

	virtual dom::Document *	load(const std::string & filename);

private:
	// Token string clean-up helpers
	static std::string	trimToken(const std::string & s);
	static std::string	cleanAttributeName(const std::string & s);
	static std::string	cleanAttributeValue(const std::string & s);
};

#endif // XMLLOADER_H
