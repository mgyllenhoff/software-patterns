#include "StandardDOMNodeFactory.H"

// Initialize static instance pointer to null
StandardDOMNodeFactory * StandardDOMNodeFactory::_instance = 0;

// Protected default constructor prevents direct instantiation
StandardDOMNodeFactory::StandardDOMNodeFactory()
{
}

// Returns the single instance, creating it on first call
StandardDOMNodeFactory * StandardDOMNodeFactory::Instance()
{
	if (_instance == 0)
	{
		_instance = new StandardDOMNodeFactory;
	}

	return _instance;
}

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
