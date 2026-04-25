#include "InsideAttributeState.H"
#include "XMLParser.H"

void InsideAttributeState::handle(XMLParser *				ctx,
				   XMLTokenizer::XMLToken::TokenTypes	type,
				   const std::string &			raw)
{
	if (type == XMLTokenizer::XMLToken::ATTRIBUTE_VALUE)
	{
		ctx->getBuilder()->addAttribute(
			ctx->getPendingAttributeName(),
			XMLParser::trimAttributeValue(raw));

		ctx->clearPendingAttributeName();
		ctx->setState(ctx->getInsideElementTagState());
	}
}
