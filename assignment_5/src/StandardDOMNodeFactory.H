#pragma once

#include "DOMNodeFactory.H"

// Abstract Factory: ConcreteFactory
// Singleton: Singleton
class StandardDOMNodeFactory : public DOMNodeFactory
{
public:
	static StandardDOMNodeFactory *	Instance();

	dom::Document *	createDocument() override;
	dom::Element *	createElement(dom::Document * doc, const std::string & tag) override;
	dom::Attr *	createAttribute(dom::Document * doc, const std::string & name) override;
	dom::Text *	createText(dom::Document * doc, const std::string & data) override;

protected:
	StandardDOMNodeFactory();

private:
	static StandardDOMNodeFactory *	_instance;
};
