#pragma once

#include <string>

#include "Node.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Abstract Factory: AbstractFactory
class DOMNodeFactory
{
public:
	virtual dom::Document *	createDocument() = 0;
	virtual dom::Element *	createElement(dom::Document * doc, const std::string & tag) = 0;
	virtual dom::Attr *	createAttribute(dom::Document * doc, const std::string & name) = 0;
	virtual dom::Text *	createText(dom::Document * doc, const std::string & data) = 0;

	virtual ~DOMNodeFactory() {}
};
