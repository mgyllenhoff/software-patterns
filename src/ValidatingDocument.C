#include "ValidatingDocument.H"
#include "ValidatingElement.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"

dom::Node * ValidatingDocument::appendChild(dom::Node * newChild)
{
	dom::Node *	realChild	= unwrap(newChild);

	if (realChild->getNodeType() == dom::Node::ELEMENT_NODE)
	{
		dom::Element *	childElement	= dynamic_cast<dom::Element *>(realChild);

		if (!validator->canRootElement(childElement->getTagName()))
			throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
				"Element '" + childElement->getTagName() +
				"' is not a valid root element.");
	}

	return documentDelegate->appendChild(realChild);
}

dom::Element * ValidatingDocument::createElement(const std::string & tagName)
{
	dom::Element *	rawElement	= documentDelegate->createElement(tagName);

	// Wrap in ValidatingElement so all operations on this element are validated
	return new ValidatingElement(rawElement, validator);
}

dom::Text * ValidatingDocument::createTextNode(const std::string & data)
{
	// Text nodes are not decorated
	// Validation occurs at the parent element level when appendChild is called with a text node.
	return documentDelegate->createTextNode(data);
}

dom::Attr * ValidatingDocument::createAttribute(const std::string & name)
{
	// Attr nodes are not decorated
	// Validation occurs in ValidatingElement::setAttribute and setAttributeNode.
	return documentDelegate->createAttribute(name);
}

dom::Element * ValidatingDocument::getDocumentElement(void)
{
	return documentDelegate->getDocumentElement();
}
