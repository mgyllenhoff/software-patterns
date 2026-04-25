#ifndef INSIDEELEMENTTAGSTATE_H
#define INSIDEELEMENTTAGSTATE_H

#include "ParserState.H"

class InsideElementTagState : public ParserState
{
public:
	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	override;
};

#endif // INSIDEELEMENTTAGSTATE_H
