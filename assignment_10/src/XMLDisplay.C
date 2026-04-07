#include "XMLDisplay.H"
#include "Attr.H"	// Layer 2
#include "Text.H"	// Layer 2

// Entry point that resets the index and starts recursive render
void XMLDisplay::display(dom::Node * node)
{
	nodeIndex.clear();
	displayNode(node, 0);
}

// Look up a node by its display index
dom::Node * XMLDisplay::getNode(int index)
{
	if (index < 0 || index >= (int)nodeIndex.size())
		return nullptr;
	return nodeIndex[index];
}

// Emit two spaces per depth level
void XMLDisplay::printIndent(int depth)
{
	for (int i = 0; i < depth; i++)
		printf("  ");
}

// Recursive pre-order render
void XMLDisplay::displayNode(dom::Node * node, int depth)
{
	if (!node) return;

	int myIndex = (int)nodeIndex.size();
	nodeIndex.push_back(node);

	switch (node->getNodeType())
	{
	// Document node: print a header line, then recurse into children
	case dom::Node::DOCUMENT_NODE:
		printf("[%d] Document\n", myIndex);
		break;

	// Element node: print tag name and all attributes on one line
	case dom::Node::ELEMENT_NODE:
	{
		dom::Element * elem = dynamic_cast<dom::Element *>(node);
		printIndent(depth);
		printf("[%d] <%s>", myIndex, elem->getTagName().c_str());

		// Print attributes inline
		if (elem->hasAttributes())
		{
			dom::NodeList * attrs = elem->getAttributes();
			for (dom::NodeList::iterator it = attrs->begin(); it != attrs->end(); ++it)
			{
				dom::Attr * attr = dynamic_cast<dom::Attr *>(*it);
				printf(" @%s=\"%s\"", attr->getName().c_str(), attr->getValue().c_str());
			}
		}
		printf("\n");
		break;
	}

	// Text node: print the text content in quotes
	case dom::Node::TEXT_NODE:
	{
		dom::Text * text = dynamic_cast<dom::Text *>(node);
		printIndent(depth);
		printf("[%d] \"%s\"\n", myIndex, text->getData().c_str());
		break;
	}

	case dom::Node::ATTRIBUTE_NODE:
	default:
		break;
	}

	// Recurse into child nodes (one level deeper for elements/document)
	int childDepth = (node->getNodeType() == dom::Node::DOCUMENT_NODE) ? depth : depth + 1;
	dom::NodeList * children = node->getChildNodes();
	for (dom::NodeList::iterator it = children->begin(); it != children->end(); ++it)
		displayNode(*it, childDepth);
}
