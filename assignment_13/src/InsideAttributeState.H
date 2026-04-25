#ifndef INSIDEATTRIBUTESTATE_H
#define INSIDEATTRIBUTESTATE_H

#include "ParserState.H"

class InsideAttributeState : public ParserState
{
public:
	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	override;
};

#endif // INSIDEATTRIBUTESTATE_H
