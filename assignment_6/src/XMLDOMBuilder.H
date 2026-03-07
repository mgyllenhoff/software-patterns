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
	bool				virtualMode;	// true = create VirtualElement + skip children
	std::string			filename;	// source path used with virtual proxy

public:
	XMLDOMBuilder(DOMNodeFactory * factory);
	XMLDOMBuilder(DOMNodeFactory * factory, const std::string & filename);
	XMLDOMBuilder(DOMNodeFactory * factory, dom::Element * root);

	void		beginElement(const std::string & name) override;
	void		addAttribute(const std::string & name, const std::string & value) override;
	void		addText(const std::string & data) override;
	void		endElement() override;
	dom::Document *	getDocument() override;

	// DOMBuilder hook overrides
	void		openTagComplete(std::streampos pos) override;
	bool		shouldSkipChildren() override;
};
