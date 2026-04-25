#include "PrettyNodeVisitor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void PrettyNodeVisitor::writeIndentation()
{
	for (int i = 0; i < indentationLevel; i++)
		file << "\t";
}

void PrettyNodeVisitor::visitDocumentEnter(dom::Document * /* node */)
{
	file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
	file << "\n";
}

void PrettyNodeVisitor::visitDocumentLeave(dom::Document * /* node */)
{
	// nothing to close for the document wrapper
}

void PrettyNodeVisitor::visitElementEnter(dom::Element * node)
{
	writeIndentation();
	file << "<" << node->getTagName();

	int	attrCount	= 0;

	for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
	  i != node->getAttributes()->end();
	  i++)
	{
		visitAttr(dynamic_cast<dom::Attr *>(*i));
		attrCount++;
	}

	if (attrCount > 0)
		file << " ";

	if (node->getChildNodes()->size() == 0)
	{
		file << "/>";
		file << "\n";
	}
	else
	{
		file << ">";
		file << "\n";
		indentationLevel++;
	}
}

void PrettyNodeVisitor::visitElementLeave(dom::Element * node)
{
	if (node->getChildNodes()->size() > 0)
	{
		indentationLevel--;
		writeIndentation();
		file << "</" << node->getTagName() << ">";
		file << "\n";
	}
}

void PrettyNodeVisitor::visitText(dom::Text * node)
{
	writeIndentation();
	file << node->getData();
	file << "\n";
}

void PrettyNodeVisitor::visitAttr(dom::Attr * node)
{
	file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}
