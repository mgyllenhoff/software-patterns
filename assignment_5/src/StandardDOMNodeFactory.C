#include "StandardDOMNodeFactory.H"

dom::Document * StandardDOMNodeFactory::createDocument()
{
	return new Document_Impl;
}

dom::Element * StandardDOMNodeFactory::createElement(dom::Document * doc, const std::string & tag)
{
	return doc->createElement(tag);
}

dom::Attr * StandardDOMNodeFactory::createAttribute(dom::Document * doc, const std::string & name)
{
	return doc->createAttribute(name);
}

dom::Text * StandardDOMNodeFactory::createText(dom::Document * doc, const std::string & data)
{
	return doc->createTextNode(data);
}
