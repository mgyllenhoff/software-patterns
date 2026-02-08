#ifndef VALIDATING_ELEMENT_H
#define VALIDATING_ELEMENT_H

#include "ValidatingNode.H"
#include "Element.H"

// Decorator: ConcreteDecorator
// Wraps a dom::Element and validates appendChild, insertBefore,
// setAttribute, and setAttributeNode against the XMLValidator schema.
class ValidatingElement : public virtual dom::Element, public ValidatingNode
{
private:
	dom::Element *	elementDelegate;
public:
	ValidatingElement(dom::Element * component, XMLValidator * validator)
		: ValidatingNode(component, validator), elementDelegate(component) {}

	virtual ~ValidatingElement() {}

	// Validated methods (the embellishment)
	virtual dom::Node *	appendChild(dom::Node * newChild);
	virtual dom::Node *	insertBefore(dom::Node * newChild, dom::Node * refChild);
	virtual void		setAttribute(const std::string & name, const std::string & value);
	virtual dom::Attr *	setAttributeNode(dom::Attr * newAttr);

	// Delegation of dom::Element methods
	virtual const std::string &	getAttribute(const std::string & name)
		{ return elementDelegate->getAttribute(name); }
	virtual dom::Attr *		getAttributeNode(const std::string & name)
		{ return elementDelegate->getAttributeNode(name); }
	virtual dom::NodeList *		getElementsByTagName(const std::string & tagName)
		{ return elementDelegate->getElementsByTagName(tagName); }
	virtual const std::string &	getTagName(void)
		{ return elementDelegate->getTagName(); }
	virtual bool			hasAttribute(const std::string & name)
		{ return elementDelegate->hasAttribute(name); }
	virtual void			removeAttribute(const std::string & name)
		{ elementDelegate->removeAttribute(name); }
	virtual dom::Attr *		removeAttributeNode(dom::Attr * oldAttr)
		{ return elementDelegate->removeAttributeNode(oldAttr); }

	virtual dom::NamedNodeMap *	getAttributes(void)
		{ return elementDelegate->getAttributes(); }
	virtual bool			hasAttributes(void)
		{ return elementDelegate->hasAttributes(); }
};

#endif // VALIDATING_ELEMENT_H
