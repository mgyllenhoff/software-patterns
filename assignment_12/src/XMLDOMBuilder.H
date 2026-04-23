#pragma once

#include <stack>

#include "DOMBuilder.H"
#include "DOMNodeFactory.H"
#include "Element.H"

// Builder: ConcreteBuilder
// Abstract Factory: Client
class XMLDOMBuilder : public DOMBuilder
{
private:
	DOMNodeFactory *		factory;
	dom::Document *			document;
	std::stack<dom::Element *>	elementStack;

public:
	XMLDOMBuilder(DOMNodeFactory * factory);

	void		beginElement(const std::string & name) override;
	void		addAttribute(const std::string & name, const std::string & value) override;
	void		addText(const std::string & data) override;
	void		endElement() override;
	dom::Document *	getDocument() override;
};
