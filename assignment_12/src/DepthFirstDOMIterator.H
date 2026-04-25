#ifndef DEPTHFIRSTDOMITERATOR_H
#define DEPTHFIRSTDOMITERATOR_H

#include <stack>
#include "DOMIterator.H"
#include "NodeList.H"

// Visitor Pattern: ObjectStructure (enumeration part)
class DepthFirstDOMIterator : public DOMIterator
{
private:
	dom::Node *	root;
	dom::Node *	current;
	Event		event;
	bool		done;

	// Stack frame: tracks position within a parent's child list
	struct Frame
	{
		dom::Node *		parent;
		dom::NodeList::iterator	childIter;
		dom::NodeList::iterator	childEnd;
	};

	std::stack<Frame>	stack;

	void descend();

public:
	DepthFirstDOMIterator(dom::Node * root);
	virtual ~DepthFirstDOMIterator();

	virtual void		first();
	virtual void		next();
	virtual bool		isDone();
	virtual dom::Node *	currentItem();
	virtual Event		currentEvent();
};

#endif // DEPTHFIRSTDOMITERATOR_H
