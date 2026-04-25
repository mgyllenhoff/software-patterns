#include "XMLParser.H"

#include "ParserState.H"
#include "BetweenTagsState.H"
#include "InsidePrologState.H"
#include "InsideElementTagState.H"
#include "InsideAttributeState.H"
#include "InsideClosingTagState.H"

XMLParser::XMLParser(const std::string & filename, DOMBuilder * builder)
	: tokenizer(filename),
	  builder(builder),
	  state(nullptr),
	  betweenTagsState(new BetweenTagsState()),
	  insidePrologState(new InsidePrologState()),
	  insideElementTagState(new InsideElementTagState()),
	  insideAttributeState(new InsideAttributeState()),
	  insideClosingTagState(new InsideClosingTagState())
{
	state = betweenTagsState; // initial state
}

XMLParser::~XMLParser()
{
	delete betweenTagsState;
	delete insidePrologState;
	delete insideElementTagState;
	delete insideAttributeState;
	delete insideClosingTagState;
}

ParserState * XMLParser::getBetweenTagsState()		{ return betweenTagsState; }
ParserState * XMLParser::getInsidePrologState()		{ return insidePrologState; }
ParserState * XMLParser::getInsideElementTagState()	{ return insideElementTagState; }
ParserState * XMLParser::getInsideAttributeState()	{ return insideAttributeState; }
ParserState * XMLParser::getInsideClosingTagState()	{ return insideClosingTagState; }

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

// Eeach ConcreteState owns the behaviour for its region of the XML grammar and
// transitions the context when a boundary token is encountered
void XMLParser::parse()
{
	while (true)
	{
		XMLTokenizer::XMLToken * token = tokenizer.getNextToken();
		XMLTokenizer::XMLToken::TokenTypes type = token->getTokenType();
		std::string raw = token->getToken();
		delete token;

		if (type == XMLTokenizer::XMLToken::NULL_TOKEN)
			return; // end of file

		state->handle(this, type, raw); // delegate to current ConcreteState
	}
}
