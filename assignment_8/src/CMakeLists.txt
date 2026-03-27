cmake_minimum_required (VERSION 3.23)
project (Patterns)

add_executable(Patterns Test.C)
set_property(TARGET Patterns PROPERTY CXX_STANDARD 20)
target_sources(Patterns PUBLIC
	Attr.C
	Attr.H
	Document.C
	Document.H
	DOMBuilder.C
	DOMBuilder.H
	DOMParseMediator.C
	DOMParseMediator.H
	Element.C
	Element.H
	NamedNodeMap.C
	NamedNodeMap.H
	Node.C
	Node.H
	NodeList.H
	Mediator.H
	Observer.H
	ParseStatusObserver.C
	ParseStatusObserver.H
	Test.C
	Text.C
	Text.H
	XMLSerializer.C
	XMLSerializer.H
	XMLTokenizer.C
	XMLTokenizer.H
	XMLValidator.C
	XMLValidator.H
	)
