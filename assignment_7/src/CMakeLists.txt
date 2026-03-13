cmake_minimum_required (VERSION 3.23)
project (Patterns)

add_executable(Patterns Test.C)
set_property(TARGET Patterns PROPERTY CXX_STANDARD 20)

target_include_directories(Patterns PUBLIC ../xerces)

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
	XMLTokenizer.C
	XMLTokenizer.H
	XMLValidator.C
	XMLValidator.H
	DOMNodeAdapter.C
	DOMNodeAdapter.H
	DOMNodeListAdapter.C
	DOMNodeListAdapter.H
	DOMNamedNodeMapAdapter.C
	DOMNamedNodeMapAdapter.H
	DOMDocumentAdapter.C
	DOMDocumentAdapter.H
	DOMElementAdapter.C
	DOMElementAdapter.H
	DOMAttrAdapter.C
	DOMAttrAdapter.H
	DOMTextAdapter.C
	DOMTextAdapter.H
	)
