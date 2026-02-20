#pragma once

#include <string>

#include "XMLTokenizer.H"
#include "DOMBuilder.H"

// Builder: Director
class XMLParser
{
private:
	XMLTokenizer	tokenizer;
	DOMBuilder *	builder;

	static std::string	trimElementName(const std::string & token);
	static std::string	trimAttributeName(const std::string & token);
	static std::string	trimAttributeValue(const std::string & token);
	static std::string	trimWhitespace(const std::string & token);

public:
	XMLParser(const std::string & filename, DOMBuilder * builder);

	void	parse();
};
