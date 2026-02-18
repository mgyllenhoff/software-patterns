#include "CompositeNode.H"

CompositeNode_Impl::CompositeNode_Impl(const std::string & name, short type) : Node_Impl(name, type)
{
}

CompositeNode_Impl::~CompositeNode_Impl()
{
}

dom::NodeList *		CompositeNode_Impl::getChildNodes(void)
{
	return &nodes;
}

dom::Node *		CompositeNode_Impl::getFirstChild(void)
{
	return *nodes.begin();
}

dom::Node *		CompositeNode_Impl::getLastChild(void)
{
	return *(--nodes.end());
}

dom::Node *		CompositeNode_Impl::insertBefore(dom::Node * newChild, dom::Node * refChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		dynamic_cast<dom::CompositeNode *>(newChild->getParentNode())->removeChild(newChild);

	if (refChild == 0)
	{
		nodes.push_back(newChild);
		(dynamic_cast<Node_Impl *>(newChild))->setParent(this);
		return newChild;
	}

	dom::NodeList::iterator	index	= nodes.find(refChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Reference Child is not a child of this node.");

	nodes.insert(++index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);

	return newChild;
}

dom::Node *		CompositeNode_Impl::replaceChild(dom::Node * newChild, dom::Node * oldChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		dynamic_cast<dom::CompositeNode *>(newChild->getParentNode())->removeChild(newChild);

	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	nodes.insert(index, newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);
	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		CompositeNode_Impl::removeChild(dom::Node * oldChild)
{
	dom::NodeList::iterator	index	= nodes.find(oldChild);

	if (index == nodes.end())
		throw dom::DOMException(dom::DOMException::NOT_FOUND_ERR, "Old Child is not a child of this node.");

	(dynamic_cast<Node_Impl *>(*index))->setParent(0);
	nodes.erase(index);

	return oldChild;
}

dom::Node *		CompositeNode_Impl::appendChild(dom::Node * newChild)
{
	if (newChild->getOwnerDocument() != getOwnerDocument())
		throw dom::DOMException(dom::DOMException::WRONG_DOCUMENT_ERR, "New Child is not a part of this document.");

	if (newChild->getParentNode() != 0)
		dynamic_cast<dom::CompositeNode *>(newChild->getParentNode())->removeChild(newChild);

	nodes.push_back(newChild);
	(dynamic_cast<Node_Impl *>(newChild))->setParent(this);

	return newChild;
}

bool			CompositeNode_Impl::hasChildNodes(void)
{
	return nodes.size() > 0;
}
