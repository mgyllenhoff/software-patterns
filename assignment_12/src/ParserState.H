#ifndef PARSERSTATE_H
#define PARSERSTATE_H

#include "XMLTokenizer.H"

class XMLParser;

// State Pattern: State
class ParserState
{
public:
	virtual ~ParserState() {}

	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	= 0;
};

#endif // PARSERSTATE_H
