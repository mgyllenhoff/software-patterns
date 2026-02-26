#include "XMLParser.H"

// Normal constructor
// Creates its own tokenizer from a filename
XMLParser::XMLParser(const std::string & filename, DOMBuilder * builder)
	: tokenizer(std::make_unique<XMLTokenizer>(filename)), builder(builder)
{
}

// Injected tokenizer constructor
// Takes ownership of a pre-seeked tokenizer (used by VirtualElement::materialize()).
XMLParser::XMLParser(XMLTokenizer * tok, DOMBuilder * builder)
	: tokenizer(tok), builder(builder)
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

// Skips all tokens belonging to the children of the current element, tracking
// nesting depth, until the matching close tag is consumed
// Then calls builder->endElement() to pop the element off the builder's stack
void XMLParser::skipToMatchingCloseTag()
{
	int  depth        = 1;
	bool inClosingTag = false;

	while (depth > 0)
	{
		XMLTokenizer::XMLToken * token = tokenizer->getNextToken();
		XMLTokenizer::XMLToken::TokenTypes type = token->getTokenType();
		delete token;

		switch (type)
		{
		case XMLTokenizer::XMLToken::NULL_TOKEN:
			return;

		case XMLTokenizer::XMLToken::TAG_START:
			inClosingTag = false;
			break;

		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			inClosingTag = true;
			break;

		case XMLTokenizer::XMLToken::ELEMENT:
			if (!inClosingTag) depth++;
			break;

		case XMLTokenizer::XMLToken::NULL_TAG_END:
			depth--;
			inClosingTag = false;
			break;

		case XMLTokenizer::XMLToken::TAG_END:
			if (inClosingTag) depth--;
			inClosingTag = false;
			break;

		default:
			break;
		}
	}

	builder->endElement();	// pop stack
}

// Loops over every token and dispatches to the appropriate builder method
// After each opening '>', calls builder->openTagComplete() with the current
// byte offset
// If builder->shouldSkipChildren() returns true, skips the entire subtree 
// Used for the virtual-proxy initial parse pass
void XMLParser::parse()
{
	std::string	pendingAttributeName;
	bool		inClosingTag	= false;
	bool		inProlog	= false;

	while (true)
	{
		XMLTokenizer::XMLToken * token = tokenizer->getNextToken();
		XMLTokenizer::XMLToken::TokenTypes type = token->getTokenType();
		std::string raw = token->getToken();
		delete token;

		switch (type)
		{
		// End of file
		case XMLTokenizer::XMLToken::NULL_TOKEN:
			return;

		// Prolog: <?xml version="1.0" encoding="UTF-8"?>
		case XMLTokenizer::XMLToken::PROLOG_START:
			inProlog = true;
			break;

		case XMLTokenizer::XMLToken::PROLOG_END:
			inProlog = false;
			break;

		case XMLTokenizer::XMLToken::PROLOG_IDENTIFIER:
			break;

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
			break;

		// Attribute name
		case XMLTokenizer::XMLToken::ATTRIBUTE:
			if (!inProlog)
				pendingAttributeName = trimAttributeName(raw);
			break;

		// Attribute value
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
		case XMLTokenizer::XMLToken::TAG_END:
			if (inProlog)
				inProlog = false;
			else if (inClosingTag)
				builder->endElement();
			else
			{
				// Opening tag just ended so notify builder of children-start
				// position, then optionally skip entire subtree
				builder->openTagComplete(tokenizer->getCurrentPosition());
				if (builder->shouldSkipChildren())
					skipToMatchingCloseTag();
			}
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

// Parses the children of the element currently being materialized
// Tracks nesting depth and returns when the matching close tag at depth 0 is
// reached (does NOT call endElement() for that close tag)
// The root element (pre-pushed in root-element-mode XMLDOMBuilder) stays on the stack
void XMLParser::parseChildren()
{
	std::string	pendingAttributeName;
	bool		inClosingTag	= false;
	int		depth		= 0;

	while (true)
	{
		XMLTokenizer::XMLToken * token = tokenizer->getNextToken();
		XMLTokenizer::XMLToken::TokenTypes type = token->getTokenType();
		std::string raw = token->getToken();
		delete token;

		switch (type)
		{
		case XMLTokenizer::XMLToken::NULL_TOKEN:
			return;

		case XMLTokenizer::XMLToken::TAG_START:
			inClosingTag = false;
			break;

		case XMLTokenizer::XMLToken::TAG_CLOSE_START:
			inClosingTag = true;
			break;

		case XMLTokenizer::XMLToken::ELEMENT:
			if (!inClosingTag)
			{
				builder->beginElement(trimElementName(raw));
				depth++;
			}
			break;

		case XMLTokenizer::XMLToken::ATTRIBUTE:
			pendingAttributeName = trimAttributeName(raw);
			break;

		case XMLTokenizer::XMLToken::ATTRIBUTE_VALUE:
			if (!pendingAttributeName.empty())
			{
				builder->addAttribute(pendingAttributeName, trimAttributeValue(raw));
				pendingAttributeName.clear();
			}
			break;

		case XMLTokenizer::XMLToken::NULL_TAG_END:
			builder->endElement();
			depth--;
			inClosingTag = false;
			break;

		case XMLTokenizer::XMLToken::TAG_END:
			if (inClosingTag)
			{
				if (depth == 0)
					return;
				builder->endElement();
				depth--;
			}
			inClosingTag = false;
			break;

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
