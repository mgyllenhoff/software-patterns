#include "DepthFirstDOMIterator.H"
#include "CompositeNode.H"

DepthFirstDOMIterator::DepthFirstDOMIterator(dom::Node * root)
	: root(root), current(0), event(ENTERING), done(true)
{
}

DepthFirstDOMIterator::~DepthFirstDOMIterator()
{
}

// Push the current node's children onto the stack and descend to the first child
void DepthFirstDOMIterator::descend()
{
	dom::CompositeNode * composite = dynamic_cast<dom::CompositeNode *>(current);

	if (composite != 0)
	{
		dom::NodeList * children = composite->getChildNodes();

		if (children != 0 && children->size() > 0)
		{
			Frame frame;
			frame.parent	= current;
			frame.childIter	= children->begin();
			frame.childEnd	= children->end();
			stack.push(frame);

			current	= *(stack.top().childIter);
			event	= ENTERING;
			return;
		}
	}

	// Leaf node or empty composite, immediately transition to LEAVING
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
		// We just entered this node
		// Try to descend into its children
		descend();
	}
	else // event == LEAVING
	{
		if (stack.empty())
		{
			// Traversal complete
			done = true;
			return;
		}

		// Advance to the next sibling in the parent's child list
		Frame & frame = stack.top();
		++(frame.childIter);

		if (frame.childIter != frame.childEnd)
		{
			// Move to next sibling
			current	= *(frame.childIter);
			event	= ENTERING;
		}
		else
		{
			// No more siblings — leave the parent
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
