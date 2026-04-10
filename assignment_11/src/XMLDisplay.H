#ifndef XMLDISPLAY_H
#define XMLDISPLAY_H

#include "Node.H"
#include "Element.H"

// Layer 4: Presentation Layer
// Command Pattern: Receiver
class XMLDisplay
{
private:
	std::vector<dom::Node *>	nodeIndex;

	virtual void	displayNode(dom::Node * node, int depth);
	virtual void	printIndent(int depth);

public:
	XMLDisplay(void)	{}
	virtual ~XMLDisplay()	{}

	virtual void		display(dom::Node * node);
	virtual dom::Node *	getNode(int index);
	virtual int		nodeCount(void)	{ return (int)nodeIndex.size(); }
};

#endif // XMLDISPLAY_H
