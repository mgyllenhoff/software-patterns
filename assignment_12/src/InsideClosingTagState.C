#include "InsideClosingTagState.H"
#include "XMLParser.H"

void InsideClosingTagState::handle(XMLParser *				ctx,
				    XMLTokenizer::XMLToken::TokenTypes	type,
				    const std::string & /* raw */)
{
	switch (type)
	{
	case XMLTokenizer::XMLToken::TAG_END:
		ctx->getBuilder()->endElement();
		ctx->setState(ctx->getBetweenTagsState());
		break;

	default:
		break;
	}
}
