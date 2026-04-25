#include "MinimalNodeVisitor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void MinimalNodeVisitor::visitDocumentEnter(dom::Document * /* node */)
{
	file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
}

void MinimalNodeVisitor::visitDocumentLeave(dom::Document * /* node */)
{
	// nothing to close for the document wrapper
}

void MinimalNodeVisitor::visitElementEnter(dom::Element * node)
{
	file << "<" << node->getTagName();

	for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
	  i != node->getAttributes()->end();
	  i++)
	{
		visitAttr(dynamic_cast<dom::Attr *>(*i));
	}

	if (node->getChildNodes()->size() == 0)
		file << "/>";
	else
		file << ">";
}

void MinimalNodeVisitor::visitElementLeave(dom::Element * node)
{
	if (node->getChildNodes()->size() > 0)
		file << "</" << node->getTagName() << ">";
}

void MinimalNodeVisitor::visitText(dom::Text * node)
{
	file << node->getData();
}

void MinimalNodeVisitor::visitAttr(dom::Attr * node)
{
	file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}
