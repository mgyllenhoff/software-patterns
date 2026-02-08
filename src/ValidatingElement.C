#include "ValidatingElement.H"
#include "Text.H"
#include "Attr.H"

dom::Node * ValidatingElement::appendChild(dom::Node * newChild)
{
	dom::Node *	realChild	= unwrap(newChild);

	if (realChild->getNodeType() == dom::Node::ELEMENT_NODE)
	{
		dom::Element *	childElement	= dynamic_cast<dom::Element *>(realChild);

		if (!validator->canAddElement(elementDelegate, childElement->getTagName()))
			throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
				"Element '" + childElement->getTagName() +
				"' is not a valid child of '" + elementDelegate->getTagName() + "'.");
	}
	else if (realChild->getNodeType() == dom::Node::TEXT_NODE)
	{
		if (!validator->canAddText(elementDelegate))
			throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
				"Text content is not allowed in element '" +
				elementDelegate->getTagName() + "'.");
	}

	return elementDelegate->appendChild(realChild);
}

dom::Node * ValidatingElement::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	dom::Node *	realChild	= unwrap(newChild);
	dom::Node *	realRef		= unwrap(refChild);

	if (realChild->getNodeType() == dom::Node::ELEMENT_NODE)
	{
		dom::Element *	childElement	= dynamic_cast<dom::Element *>(realChild);

		if (!validator->canAddElement(elementDelegate, childElement->getTagName()))
			throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
				"Element '" + childElement->getTagName() +
				"' is not a valid child of '" + elementDelegate->getTagName() + "'.");
	}
	else if (realChild->getNodeType() == dom::Node::TEXT_NODE)
	{
		if (!validator->canAddText(elementDelegate))
			throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
				"Text content is not allowed in element '" +
				elementDelegate->getTagName() + "'.");
	}

	return elementDelegate->insertBefore(realChild, realRef);
}

void ValidatingElement::setAttribute(const std::string & name, const std::string & value)
{
	if (!validator->canAddAttribute(elementDelegate, name))
		throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
			"Attribute '" + name + "' is not valid on element '" +
			elementDelegate->getTagName() + "'.");

	elementDelegate->setAttribute(name, value);
}

dom::Attr * ValidatingElement::setAttributeNode(dom::Attr * newAttr)
{
	if (!validator->canAddAttribute(elementDelegate, newAttr->getName()))
		throw dom::DOMException(dom::DOMException::HIERARCHY_REQUEST_ERR,
			"Attribute '" + newAttr->getName() + "' is not valid on element '" +
			elementDelegate->getTagName() + "'.");

	return elementDelegate->setAttributeNode(newAttr);
}
