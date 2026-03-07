#pragma once

#include <string>

#include "XMLTokenizer.H"
#include "DOMBuilder.H"

// Builder: Director
class XMLParser
{
private:
	std::unique_ptr<XMLTokenizer>	tokenizer;
	DOMBuilder *			builder;

	static std::string	trimElementName(const std::string & token);
	static std::string	trimAttributeName(const std::string & token);
	static std::string	trimAttributeValue(const std::string & token);
	static std::string	trimWhitespace(const std::string & token);
	void	skipToMatchingCloseTag();

public:
	XMLParser(const std::string & filename, DOMBuilder * builder);
	XMLParser(XMLTokenizer * tok, DOMBuilder * builder);

	void	parse();
	void	parseChildren();
};
