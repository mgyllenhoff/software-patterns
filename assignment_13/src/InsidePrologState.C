#include "InsidePrologState.H"
#include "XMLParser.H"

void InsidePrologState::handle(XMLParser *				ctx,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string & /* token */)
{
	switch (type)
	{
	// End of prolog 
	case XMLTokenizer::XMLToken::PROLOG_END:
	case XMLTokenizer::XMLToken::TAG_END:
		ctx->setState(ctx->getBetweenTagsState());
		break;

	// PROLOG_IDENTIFIER, ATTRIBUTE, ATTRIBUTE_VALUE
	default:
		break;
	}
}
