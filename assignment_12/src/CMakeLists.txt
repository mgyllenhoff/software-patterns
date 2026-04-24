cmake_minimum_required (VERSION 3.23)
project (Patterns)

add_executable(Patterns Test.C)
set_property(TARGET Patterns PROPERTY CXX_STANDARD 20)
target_sources(Patterns PUBLIC
	Attr.C
	Attr.H
	Document.C
	Document.H
	Element.C
	Element.H
	NamedNodeMap.C
	NamedNodeMap.H
	Node.C
	Node.H
	NodeList.H
	Test.C
	Text.C
	Text.H
	XMLSerializer.C
	XMLSerializer.H
	PrettyXMLSerializer.C
	PrettyXMLSerializer.H
	MinimalXMLSerializer.C
	MinimalXMLSerializer.H
	XMLTokenizer.C
	XMLTokenizer.H
	XMLValidator.C
	XMLValidator.H
	DOMNodeFactory.H
	StandardDOMNodeFactory.C
	StandardDOMNodeFactory.H
	DOMBuilder.H
	XMLDOMBuilder.C
	XMLDOMBuilder.H
	XMLParser.C
	XMLParser.H
	NodeProcessor.H
	PrettyNodeProcessor.H
	PrettyNodeProcessor.C
	MinimalNodeProcessor.H
	MinimalNodeProcessor.C
	DOMIterator.H
	DepthFirstDOMIterator.H
	DepthFirstDOMIterator.C
	ParserState.H
	BetweenTagsState.H
	BetweenTagsState.C
	InsidePrologState.H
	InsidePrologState.C
	InsideElementTagState.H
	InsideElementTagState.C
	InsideAttributeState.H
	InsideAttributeState.C
	InsideClosingTagState.H
	InsideClosingTagState.C
	)
