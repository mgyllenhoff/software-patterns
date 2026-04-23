#pragma once

#include "DOMNodeFactory.H"

// Abstract Factory: ConcreteFactory
class StandardDOMNodeFactory : public DOMNodeFactory
{
public:
	dom::Document *	createDocument() override;
	dom::Element *	createElement(dom::Document * doc, const std::string & tag) override;
	dom::Attr *	createAttribute(dom::Document * doc, const std::string & name) override;
	dom::Text *	createText(dom::Document * doc, const std::string & data) override;
};
