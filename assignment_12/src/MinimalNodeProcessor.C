#include "MinimalNodeProcessor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void MinimalNodeProcessor::processDocumentOpen(dom::Document * node)
{
	file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
}

void MinimalNodeProcessor::processDocumentClose(dom::Document * node)
{
}

// Strategy Pattern: ConcreteStrategy operation
void MinimalNodeProcessor::processElementOpen(dom::Element * node)
{
	file << "<" << node->getTagName();

	for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
	  i != node->getAttributes()->end();
	  i++)
	{
		processAttr(dynamic_cast<dom::Attr *>(*i));
	}

	if (node->getChildNodes()->size() == 0)
		file << "/>";
	else
		file << ">";
}

void MinimalNodeProcessor::processElementClose(dom::Element * node)
{
	if (node->getChildNodes()->size() > 0)
		file << "</" << node->getTagName() << ">";
}

void MinimalNodeProcessor::processAttr(dom::Attr * node)
{
	file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}

void MinimalNodeProcessor::processText(dom::Text * node)
{
	file << node->getData();
}
