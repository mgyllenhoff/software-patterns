#pragma once

#include <string>

#include "XMLTokenizer.H"
#include "DOMBuilder.H"

class ParserState;
class BetweenTagsState;
class InsidePrologState;
class InsideElementTagState;
class InsideAttributeState;
class InsideClosingTagState;

class XMLParser
{
private:
	XMLTokenizer	tokenizer;
	DOMBuilder *	builder;

	// current state (Context maintains this instance)
	ParserState *	state;

	// Shared data passed between states during transitions
	std::string	pendingAttributeName;

	// Owned ConcreteState instances that are reused across transitions
	BetweenTagsState *	    betweenTagsState;
	InsidePrologState *	    insidePrologState;
	InsideElementTagState * insideElementTagState;
	InsideAttributeState *  insideAttributeState;
	InsideClosingTagState * insideClosingTagState;

public:
	XMLParser(const std::string & filename, DOMBuilder * builder);
	~XMLParser();

	void	parse();
	void	setState(ParserState * s)	{ state = s; }

	ParserState *	getBetweenTagsState();
	ParserState *	getInsidePrologState();
	ParserState *	getInsideElementTagState();
	ParserState *	getInsideAttributeState();
	ParserState *	getInsideClosingTagState();

	DOMBuilder *		getBuilder()					{ return builder; }
	void			setPendingAttributeName(const std::string & name)	{ pendingAttributeName = name; }
	const std::string &	getPendingAttributeName()	const			{ return pendingAttributeName; }
	void			clearPendingAttributeName()				{ pendingAttributeName.clear(); }

	static std::string	trimElementName(const std::string & token);
	static std::string	trimAttributeName(const std::string & token);
	static std::string	trimAttributeValue(const std::string & token);
	static std::string	trimWhitespace(const std::string & token);
};
