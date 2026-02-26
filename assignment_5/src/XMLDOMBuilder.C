#include "XMLDOMBuilder.H"
#include "VirtualElement.H"

// Normal (eager parse)
XMLDOMBuilder::XMLDOMBuilder(DOMNodeFactory * factory)
	: factory(factory), virtualMode(false), filename("")
{
	document = factory->createDocument();
}

// Virtual Proxy
// beginElement() creates VirtualElement objects
// Parser is asked to skip children after each opening tag
XMLDOMBuilder::XMLDOMBuilder(DOMNodeFactory * factory, const std::string & filename)
	: factory(factory), virtualMode(true), filename(filename)
{
	document = factory->createDocument();
}

// Root-element
// Used during VirtualElement::materialize() to populate an existing element
// Pre-pushes the existing element so beginElement() appends children directly to it
XMLDOMBuilder::XMLDOMBuilder(DOMNodeFactory * factory, dom::Element * root)
	: factory(factory), virtualMode(false), filename("")
{
	document = root->getOwnerDocument();
	elementStack.push(root);
}

// Creates an element, appends it to the current parent (or the document if
// this is the root), then pushes it onto the stack so subsequent calls
// operate on it as the new current element.
// With virtual proxy, creates VirtualElement instead of default
void XMLDOMBuilder::beginElement(const std::string & name)
{
	dom::Element * elem = virtualMode
		? new VirtualElement(name, document, filename)
		: factory->createElement(document, name);

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

dom::Document * XMLDOMBuilder::getDocument()
{
	return document;
}

// With virtual proxy, records the children-start byte offset on the top-of-stack
// VirtualElement so it knows where to seek when materialize() is called
void XMLDOMBuilder::openTagComplete(std::streampos pos)
{
	if (!virtualMode) return;
	VirtualElement * ve = dynamic_cast<VirtualElement *>(elementStack.top());
	if (ve) ve->setChildrenStart(pos);
}

// Tell the parser to skip children when in virtual mode
bool XMLDOMBuilder::shouldSkipChildren()
{
	return virtualMode;
}
