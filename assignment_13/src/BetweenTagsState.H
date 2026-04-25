#ifndef BETWEENTAGSSTATE_H
#define BETWEENTAGSSTATE_H

#include "ParserState.H"

class BetweenTagsState : public ParserState
{
public:
	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	override;
};

#endif // BETWEENTAGSSTATE_H
