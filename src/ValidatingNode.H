#ifndef VALIDATING_NODE_H
#define VALIDATING_NODE_H

#include "Node.H"
#include "XMLValidator.H"

// Decorator Pattern: Decorator
class ValidatingNode : public virtual dom::Node
{
protected:
	dom::Node *	component;
	XMLValidator *	validator;

	ValidatingNode(dom::Node * component, XMLValidator * validator)
		: component(component), validator(validator) {}

public:
	virtual ~ValidatingNode() {}

	// Returns the underlying concrete node
	dom::Node *	getComponent(void)	{ return component; }

	// Unwrap a node if it is a decorator, otherwise return as-is
	static dom::Node * unwrap(dom::Node * node)
	{
		ValidatingNode * vn = dynamic_cast<ValidatingNode *>(node);
		return vn ? vn->getComponent() : node;
	}

	// All dom::Node methods delegate to component
	virtual const std::string &	getNodeName(void)				{ return component->getNodeName(); }
	virtual const std::string &	getNodeValue(void)				{ return component->getNodeValue(); }
	virtual void			setNodeValue(const std::string & nodeValue)	{ component->setNodeValue(nodeValue); }
	virtual short			getNodeType(void)				{ return component->getNodeType(); }
	virtual dom::Node *		getParentNode(void)				{ return component->getParentNode(); }
	virtual dom::NodeList *		getChildNodes(void)				{ return component->getChildNodes(); }
	virtual dom::Node *		getFirstChild(void)				{ return component->getFirstChild(); }
	virtual dom::Node *		getLastChild(void)				{ return component->getLastChild(); }
	virtual dom::Node *		getPreviousSibling(void)			{ return component->getPreviousSibling(); }
	virtual dom::Node *		getNextSibling(void)				{ return component->getNextSibling(); }
	virtual dom::Document *		getOwnerDocument(void)				{ return component->getOwnerDocument(); }
	virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild)
		{ return component->insertBefore(unwrap(newChild), unwrap(refChild)); }
	virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild)
		{ return component->replaceChild(unwrap(newChild), unwrap(oldChild)); }
	virtual dom::Node *		removeChild(dom::Node * oldChild)
		{ return component->removeChild(unwrap(oldChild)); }
	virtual dom::Node *		appendChild(dom::Node * newChild)
		{ return component->appendChild(unwrap(newChild)); }
	virtual bool			hasChildNodes(void)				{ return component->hasChildNodes(); }
	virtual const std::string &	getLocalName(void)				{ return component->getLocalName(); }
};

#endif // VALIDATING_NODE_H
