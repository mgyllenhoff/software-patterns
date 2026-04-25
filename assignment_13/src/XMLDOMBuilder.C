#include "XMLDOMBuilder.H"

XMLDOMBuilder::XMLDOMBuilder(DOMNodeFactory * factory)
	: factory(factory)
{
	// Create the Document immediately via the Abstract Factory
	document = factory->createDocument();
}

// Creates an element, appends it to the current parent (or the document if
// this is the root), then pushes it onto the stack so subsequent calls
// operate on it as the new current element.
void XMLDOMBuilder::beginElement(const std::string & name)
{
	dom::Element * elem = factory->createElement(document, name);

	if (elementStack.empty())
		document->appendChild(elem);	// root element
	else
		elementStack.top()->appendChild(elem);

	elementStack.push(elem);
}

// Sets a named attribute on the current element at top of stack
void XMLDOMBuilder::addAttribute(const std::string & name, const std::string & value)
{
	dom::Attr * attr = factory->createAttribute(document, name);
	attr->setValue(value);
	elementStack.top()->setAttributeNode(attr);
}

// Appends a text node as a child of the current element
void XMLDOMBuilder::addText(const std::string & data)
{
	dom::Text * text = factory->createText(document, data);
	elementStack.top()->appendChild(text);
}

// Pops the stack, returning context to the parent element
void XMLDOMBuilder::endElement()
{
	if (!elementStack.empty())
		elementStack.pop();
}

// Gets resulting document
dom::Document * XMLDOMBuilder::getDocument()
{
	return document;
}
