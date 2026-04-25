#include "DepthFirstDOMIterator.H"

DepthFirstDOMIterator::DepthFirstDOMIterator(dom::Node * root)
	: root(root), current(0), event(ENTERING), done(true)
{
}

DepthFirstDOMIterator::~DepthFirstDOMIterator()
{
}

void DepthFirstDOMIterator::descend()
{
	dom::NodeList *	children	= current->getChildNodes();

	if (children != 0 && children->size() > 0)
	{
		Frame	frame;
		frame.parent	= current;
		frame.childIter	= children->begin();
		frame.childEnd	= children->end();
		stack.push(frame);

		current	= *(stack.top().childIter);
		event	= ENTERING;
		return;
	}

	// Leaf node or empty composite so immediately transition to LEAVING
	event = LEAVING;
}

void DepthFirstDOMIterator::first()
{
	// Clear any previous traversal state
	while (!stack.empty())
		stack.pop();

	current	= root;
	event	= ENTERING;
	done	= false;
}

void DepthFirstDOMIterator::next()
{
	if (done)
		return;

	if (event == ENTERING)
	{
		// Just entered this node so try to descend into its children
		descend();
	}
	else // LEAVING
	{
		if (stack.empty())
		{
			// Finished leaving the root so traversal is complete
			done = true;
			return;
		}

		// Advance to the next sibling in the parent's child list
		Frame &	frame	= stack.top();
		++(frame.childIter);

		if (frame.childIter != frame.childEnd)
		{
			// Move to the next sibling
			current	= *(frame.childIter);
			event	= ENTERING;
		}
		else
		{
			// No more siblings so leave the parent
			current	= frame.parent;
			event	= LEAVING;
			stack.pop();
		}
	}
}

bool DepthFirstDOMIterator::isDone()
{
	return done;
}

dom::Node * DepthFirstDOMIterator::currentItem()
{
	return current;
}

DOMIterator::Event DepthFirstDOMIterator::currentEvent()
{
	return event;
}
