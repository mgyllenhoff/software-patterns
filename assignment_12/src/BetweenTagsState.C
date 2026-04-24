#include "BetweenTagsState.H"
#include "XMLParser.H"

void BetweenTagsState::handle(XMLParser *				ctx,
			       XMLTokenizer::XMLToken::TokenTypes	type,
			       const std::string &			raw)
{
	switch (type)
	{
	// XML prolog: <?xml ... ?>
	case XMLTokenizer::XMLToken::PROLOG_START:
		ctx->setState(ctx->getInsidePrologState());
		break;

	// Opening tag: <tagname
	case XMLTokenizer::XMLToken::TAG_START:
		ctx->setState(ctx->getInsideElementTagState());
		break;

	// Closing tag: </tagname>
	case XMLTokenizer::XMLToken::TAG_CLOSE_START:
		ctx->setState(ctx->getInsideClosingTagState());
		break;

	// Text content between elements
	case XMLTokenizer::XMLToken::VALUE:
	{
		std::string text = XMLParser::trimWhitespace(raw);
		if (!text.empty())
			ctx->getBuilder()->addText(text);
		break;
	}

	default:
		break;
	}
}
