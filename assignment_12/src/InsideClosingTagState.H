#ifndef INSIDECLOSINGTAGSTATE_H
#define INSIDECLOSINGTAGSTATE_H

#include "ParserState.H"

// State Pattern: ConcreteState
class InsideClosingTagState : public ParserState
{
public:
	virtual void	handle(XMLParser *				context,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			token)	override;
};

#endif // INSIDECLOSINGTAGSTATE_H
