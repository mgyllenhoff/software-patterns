#include "InsideElementTagState.H"
#include "XMLParser.H"

void InsideElementTagState::handle(XMLParser *				ctx,
				    XMLTokenizer::XMLToken::TokenTypes	type,
				    const std::string &			raw)
{
	switch (type)
	{
	case XMLTokenizer::XMLToken::ELEMENT:
		ctx->getBuilder()->beginElement(XMLParser::trimElementName(raw));
		break;

	case XMLTokenizer::XMLToken::ATTRIBUTE:
		ctx->setPendingAttributeName(XMLParser::trimAttributeName(raw));
		ctx->setState(ctx->getInsideAttributeState());
		break;

	case XMLTokenizer::XMLToken::NULL_TAG_END:
		ctx->getBuilder()->endElement();
		ctx->setState(ctx->getBetweenTagsState());
		break;

	case XMLTokenizer::XMLToken::TAG_END:
		ctx->setState(ctx->getBetweenTagsState());
		break;

	default:
		break;
	}
}
