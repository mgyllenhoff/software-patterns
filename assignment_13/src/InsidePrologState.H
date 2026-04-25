#ifndef INSIDEPROLOGSTATE_H
#define INSIDEPROLOGSTATE_H

#include "ParserState.H"

class InsidePrologState : public ParserState
{
public:
	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	override;
};

#endif // INSIDEPROLOGSTATE_H
