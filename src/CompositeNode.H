#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "Node.H"

namespace dom
{
	// Composite Pattern: Composite
	// Only node types that can have children extend this interface
	class CompositeNode : public virtual Node
	{
	public:
		virtual ~CompositeNode() {}

		virtual NodeList *		getChildNodes(void)				= 0;
		virtual Node *			getFirstChild(void)				= 0;
		virtual Node *			getLastChild(void)				= 0;
		virtual Node *			insertBefore(Node * newChild, Node * refChild)	= 0;
		virtual Node *			replaceChild(Node * newChild, Node * oldChild)	= 0;
		virtual Node *			removeChild(Node * oldChild)			= 0;
		virtual Node *			appendChild(Node * newChild)			= 0;
		virtual bool			hasChildNodes(void)				= 0;
	};
};

// Composite Pattern: Composite implementation
class CompositeNode_Impl : public virtual dom::CompositeNode, public virtual Node_Impl
{
private:
	dom::NodeList	nodes;

protected:
	CompositeNode_Impl(const std::string & name, short type);
public:
	virtual ~CompositeNode_Impl();

	virtual dom::NodeList *		getChildNodes(void);
	virtual dom::Node *		getFirstChild(void);
	virtual dom::Node *		getLastChild(void);
	virtual dom::Node *		insertBefore(dom::Node * newChild, dom::Node * refChild);
	virtual dom::Node *		replaceChild(dom::Node * newChild, dom::Node * oldChild);
	virtual dom::Node *		removeChild(dom::Node * oldChild);
	virtual dom::Node *		appendChild(dom::Node * newChild);
	virtual bool			hasChildNodes(void);
};

#endif // COMPOSITENODE_H
