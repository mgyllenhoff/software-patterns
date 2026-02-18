#ifndef DOMITERATOR_H
#define DOMITERATOR_H

#include "Node.H"

// Iterator Pattern: Iterator
// Defines an interface for accessing and traversing elements of the DOM tree.
class DOMIterator
{
public:
	enum Event { ENTERING, LEAVING };

	virtual ~DOMIterator() {}

	virtual void		first()		= 0;	// Reset to beginning of traversal
	virtual void		next()		= 0;	// Advance to next position
	virtual bool		isDone()	= 0;	// Check if traversal is complete
	virtual dom::Node *	currentItem()	= 0;	// Current node
	virtual Event		currentEvent()	= 0;	// ENTERING or LEAVING current node
};

#endif // DOMITERATOR_H
