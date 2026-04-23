#include "PrettyNodeProcessor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void PrettyNodeProcessor::writeIndentation()
{
	for (int i = 0; i < indentationLevel; i++)
		file << "\t";
}

void PrettyNodeProcessor::processDocumentOpen(dom::Document * node)
{
	file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
	file << "\n";
}

void PrettyNodeProcessor::processDocumentClose(dom::Document * node)
{
}

void PrettyNodeProcessor::processElementOpen(dom::Element * node)
{
	writeIndentation();
	file << "<" << node->getTagName();

	int	attrCount	= 0;

	for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
	  i != node->getAttributes()->end();
	  i++)
	{
		processAttr(dynamic_cast<dom::Attr *>(*i));
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

void PrettyNodeProcessor::processElementClose(dom::Element * node)
{
	if (node->getChildNodes()->size() > 0)
	{
		indentationLevel--;
		writeIndentation();
		file << "</" << node->getTagName() << ">";
		file << "\n";
	}
}

void PrettyNodeProcessor::processAttr(dom::Attr * node)
{
	file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}

void PrettyNodeProcessor::processText(dom::Text * node)
{
	writeIndentation();
	file << node->getData();
	file << "\n";
}
