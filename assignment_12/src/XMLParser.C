#include "XMLParser.H"

XMLParser::XMLParser(const std::string & filename, DOMBuilder * builder)
	: tokenizer(filename), builder(builder)
{
}

// Strip leading/trailing whitespace — ELEMENT regex may include leading spaces.
std::string XMLParser::trimElementName(const std::string & token)
{
	std::string s = token;
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
	  [](unsigned char c){ return !std::isspace(c); }));
	return s;
}

// Strip leading whitespace and trailing '=' — ATTRIBUTE regex: [[:space:]]+name[[:space:]]*=
std::string XMLParser::trimAttributeName(const std::string & token)
{
	std::string s = token;
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
	  [](unsigned char c){ return !std::isspace(c); }));
	while (!s.empty() && (std::isspace((unsigned char)s.back()) || s.back() == '='))
		s.pop_back();
	return s;
}

// Strip surrounding double-quotes — ATTRIBUTE_VALUE regex: "[^"]*"
std::string XMLParser::trimAttributeValue(const std::string & token)
{
	if (token.size() >= 2 && token.front() == '"' && token.back() == '"')
		return token.substr(1, token.size() - 2);
	return token;
}

// Strip leading and trailing whitespace from a VALUE (text content) token.
std::string XMLParser::trimWhitespace(const std::string & token)
{
	std::string s = token;
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
	  [](unsigned char c){ return !std::isspace(c); }));
	s.erase(std::find_if(s.rbegin(), s.rend(),
	  [](unsigned char c){ return !std::isspace(c); }).base(), s.end());
	return s;
}

// Loops over every token and dispatches to the appropriate builder method.
void XMLParser::parse()
{
	std::string	pendingAttributeName;
	bool		inClosingTag	= false;
	bool		inProlog	= false;

	while (true)
	{
		XMLTokenizer::XMLToken * token = tokenizer.getNextToken();
		XMLTokenizer::XMLToken::TokenTypes type = token->getTokenType();
		std::string raw = token->getToken();
		delete token;

		switch (type)
		{
		// End of file
		case XMLTokenizer::XMLToken::NULL_TOKEN:
			return;

		// Prolog: <?xml version="1.0" encoding="UTF-8"?>
		// All tokens between PROLOG_START and PROLOG_END are skipped.
		case XMLTokenizer::XMLToken::PROLOG_START:
			inProlog = true;
			break;

		case XMLTokenizer::XMLToken::PROLOG_END:
			inProlog = false;
			break;

		case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
			break;	// skip if xml identifier inside prolog

		// Tag delimiters
		case XMLTokenizer::XMLToken::TAG_START:
			inClosingTag = false;
			break;

		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			inClosingTag = true;
			break;

		// Element name
		case XMLTokenizer::XMLToken::ELEMENT:
			if (!inClosingTag)
				builder->beginElement(trimElementName(raw));
			// closing-tag name is informational — endElement() fires on TAG_END
			break;

		// Attribute name (leading spaces + trailing '=')
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			if (!inProlog)
				pendingAttributeName = trimAttributeName(raw);
			break;

		// Attribute value (surrounding quotes)
		// Used both inside the prolog and for element attributes
		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			if (!inProlog && !pendingAttributeName.empty())
			{
				builder->addAttribute(pendingAttributeName, trimAttributeValue(raw));
				pendingAttributeName.clear();
			}
			break;

		// Self-closing tag />
		case XMLTokenizer::XMLToken::NULL_TAG_END:
			builder->endElement();
			break;

		// Closing '>'
		// Also closes the prolog (<?xml ... ?> ends with TAG_END, not PROLOG_END)
		case XMLTokenizer::XMLToken::TAG_END:
			if (inProlog)
				inProlog = false;
			else if (inClosingTag)
				builder->endElement();
			inClosingTag = false;
			break;

		// Text content between tags
		case XMLTokenizer::XMLToken::VALUE:
		{
			std::string text = trimWhitespace(raw);
			if (!text.empty())
				builder->addText(text);
			break;
		}

		default:
			break;
		}
	}
}
