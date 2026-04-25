#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"
#include "NodeProcessor.H"
#include "PrettyNodeProcessor.H"
#include "MinimalNodeProcessor.H"
#include "NodeVisitor.H"
#include "PrettyNodeVisitor.H"
#include "MinimalNodeVisitor.H"
#include "DOMIterator.H"

void XMLSerializer::serialize(dom::Node * node)
{
	if (dynamic_cast<dom::Document *>(node) != 0)
	{
		file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
		writeDeclarationSuffix(); // HOOK
		serialize(dynamic_cast<dom::Document *>(node)->getDocumentElement());
	}
	else if (dynamic_cast<dom::Element *>(node) != 0)
	{
		writeBeforeOpenTag(); // HOOK
		file << "<" << dynamic_cast<dom::Element *>(node)->getTagName();

		int	attrCount	= 0;

		for (dom::NamedNodeMap::iterator i = dynamic_cast<dom::Element *>(node)->getAttributes()->begin();
		  i != dynamic_cast<dom::Element *>(node)->getAttributes()->end();
		  i++)
		{
			serialize(*i);
			attrCount++;
		}

		writeAfterAttributes(attrCount); // HOOK

		if (dynamic_cast<dom::Element *>(node)->getChildNodes()->size() == 0)
		{
			writeEmptyElementClose(); // HOOK
		}
		else
		{
			writeAfterOpenBracket(); // HOOK — writes ">", optional newline, optional indent++

			for (dom::NodeList::iterator i = dynamic_cast<dom::Element *>(node)->getChildNodes()->begin();
			  i != dynamic_cast<dom::Element *>(node)->getChildNodes()->end();
			  i++)
				if (dynamic_cast<dom::Element *>(*i) != 0 || dynamic_cast<dom::Text *>(*i) != 0)
					serialize(*i);

			beforeChildrenEnd(); // HOOK — optional indent--, optional indentation
			file << "</" << dynamic_cast<dom::Element *>(node)->getTagName() << ">";
			writeAfterCloseTag(); // HOOK
		}
	}
	else if (dynamic_cast<dom::Attr *>(node) != 0)
	{
		// invariant so no hook needed
		dom::Attr *	attr	= dynamic_cast<dom::Attr *>(node);
		file << " " << attr->getName() << "=\"" << attr->getValue() << "\"";
	}
	else if (dynamic_cast<dom::Text *>(node) != 0)
	{
		writeBeforeText(); // HOOK
		file << dynamic_cast<dom::Text *>(node)->getData();
		writeAfterText(); // HOOK
	}
}

void XMLSerializer::serializeWithProcessor(dom::Node * node, NodeProcessor & processor)
{
	DOMIterator *	it	= node->createIterator();

	for (it->first(); !it->isDone(); it->next())
	{
		dom::Node *	current	= it->currentItem();

		if (it->currentEvent() == DOMIterator::ENTERING)
		{
			if (dynamic_cast<dom::Document *>(current) != 0)
				processor.processDocumentOpen(dynamic_cast<dom::Document *>(current));
			else if (dynamic_cast<dom::Element *>(current) != 0)
				processor.processElementOpen(dynamic_cast<dom::Element *>(current));
			else if (dynamic_cast<dom::Text *>(current) != 0)
				processor.processText(dynamic_cast<dom::Text *>(current));
		}
		else // LEAVING
		{
			if (dynamic_cast<dom::Document *>(current) != 0)
				processor.processDocumentClose(dynamic_cast<dom::Document *>(current));
			else if (dynamic_cast<dom::Element *>(current) != 0)
				processor.processElementClose(dynamic_cast<dom::Element *>(current));
		}
	}

	delete it;
}

void XMLSerializer::serializePretty(dom::Node * node, std::ostream & output)
{
	PrettyNodeProcessor	processor(output);	// ConcreteStrategy selected
	serializeWithProcessor(node, processor);	// Context invokes strategy via iterator
}

void XMLSerializer::serializeMinimal(dom::Node * node, std::ostream & output)
{
	MinimalNodeProcessor	processor(output);	// ConcreteStrategy selected
	serializeWithProcessor(node, processor);	// Context invokes strategy via iterator
}

void XMLSerializer::serializeWithVisitor(dom::Node * node, NodeVisitor & visitor)
{
	DOMIterator *	it	= node->createIterator();

	for (it->first(); !it->isDone(); it->next())
	{
		dom::Node *	current	= it->currentItem();

		if (it->currentEvent() == DOMIterator::ENTERING)
			current->acceptEnter(visitor);	// first dispatch selects concrete accept()
		else
			current->acceptLeave(visitor);	// concrete accept() calls back into visitor
	}

	delete it;
}

void XMLSerializer::serializePrettyVisitor(dom::Node * node, std::ostream & output)
{
	PrettyNodeVisitor	visitor(output);	// ConcreteVisitor 1 selected
	serializeWithVisitor(node, visitor);	// ObjectStructure drives traversal
}

void XMLSerializer::serializeMinimalVisitor(dom::Node * node, std::ostream & output)
{
	MinimalNodeVisitor	visitor(output);	// ConcreteVisitor 2 selected
	serializeWithVisitor(node, visitor);	// ObjectStructure drives traversal
}
