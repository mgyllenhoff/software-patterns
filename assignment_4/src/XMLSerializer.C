#include "XMLSerializer.H"

#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

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
