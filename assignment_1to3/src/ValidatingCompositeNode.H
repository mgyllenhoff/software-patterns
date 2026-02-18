#ifndef VALIDATING_COMPOSITENODE_H
#define VALIDATING_COMPOSITENODE_H

#include "ValidatingNode.H"
#include "CompositeNode.H"

// Decorator Pattern: Decorator for CompositeNode
class ValidatingCompositeNode : public virtual dom::CompositeNode, public ValidatingNode
{
protected:
	dom::CompositeNode *	compositeComponent;

	ValidatingCompositeNode(dom::CompositeNode * component, XMLValidator * validator)
		: ValidatingNode(component, validator), compositeComponent(component) {}

public:
	virtual ~ValidatingCompositeNode() {}

	// Delegate composite methods to component
	virtual dom::NodeList *		getChildNodes(void)
		{ return compositeComponent->getChildNodes(); }
	virtual dom::Node *		getFirstChild(void)
		{ return compositeComponent->getFirstChild(); }
	virtual dom::Node *		getLastChild(void)
		{ return compositeComponent->getLastChild(); }
	virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild)
		{ return compositeComponent->insertBefore(unwrap(newChild), unwrap(refChild)); }
	virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild)
		{ return compositeComponent->replaceChild(unwrap(newChild), unwrap(oldChild)); }
	virtual dom::Node *		removeChild(dom::Node * oldChild)
		{ return compositeComponent->removeChild(unwrap(oldChild)); }
	virtual dom::Node *		appendChild(dom::Node * newChild)
		{ return compositeComponent->appendChild(unwrap(newChild)); }
	virtual bool			hasChildNodes(void)
		{ return compositeComponent->hasChildNodes(); }
};

#endif // VALIDATING_COMPOSITENODE_H
