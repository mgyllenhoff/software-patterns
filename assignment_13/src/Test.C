#include <stdio.h>
#include <fstream>
#include <iostream>
#include "Attr.H"
#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "XMLTokenizer.H"
#include "PrettyXMLSerializer.H"
#include "MinimalXMLSerializer.H"
#include "XMLSerializer.H"
#include "XMLValidator.H"
#include "StandardDOMNodeFactory.H"
#include "XMLDOMBuilder.H"
#include "XMLParser.H"

void testTokenizer(int argc, char** argv);
void testSerializer(int argc, char** argv);
void testValidator(int argc, char** argv);
void testParser(int argc, char** argv);
void testStrategySerializer(int argc, char** argv);
void testVisitorSerializer(int argc, char** argv);

void printUsage(void)
{
	printf("Usage:\n");
	printf("\tTest t [file] ...\n");
	printf("\tTest s [file1] [file2]\n");
	printf("\tTest v [file]\n");
	printf("\tTest p [file1] [file2]\n");
	printf("\tTest q [xmlfile] [outfile]   (Builder + Strategy demo)\n");
	printf("\tTest r [xmlfile] [outfile]   (Builder + Visitor demo)\n");
}

int main(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(0);
	}

	switch(argv[1][0])
	{
	case 'T':
	case 't':
		testTokenizer(argc, argv);
		break;
	case 'S':
	case 's':
		testSerializer(argc, argv);
		break;
	case 'V':
	case 'v':
		testValidator(argc, argv);
		break;
	case 'P':
	case 'p':
		testParser(argc, argv);
		break;
	case 'Q':
	case 'q':
		testStrategySerializer(argc, argv);
		break;
	case 'R':
	case 'r':
		testVisitorSerializer(argc, argv);
		break;
	}
}

void testTokenizer(int argc, char** argv)
{
	dom::Document *	document	= new Document_Impl;

	dom::Element *	element	= document->createElement("NewElement");
	dom::Text *	text	= document->createTextNode("Text Data");
	dom::Attr *	attr	= document->createAttribute("NewAttribute");

	printf("Element Tag = '%s'\n", element->getTagName().c_str());
	printf("Text Data = '%s'\n", text->getValue().c_str());
	printf("Attr Name = '%s'\n", attr->getName().c_str());

	element->setAttributeNode(attr);
	printf("Element attribute '%s'='%s'\n", element->getTagName().c_str(), element->getAttribute("NewAttribute").c_str());

	delete element;
	delete text;
	delete attr;
	delete document;

	for (int i = 2; i < argc; i++)
	{
		XMLTokenizer	tokenizer(argv[i]);

		XMLTokenizer::XMLToken *	token	= 0;

		printf("File:  '%s'\n", argv[i]);

		do
		{
			delete	token;
			token	= tokenizer.getNextToken();

			printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
			  token->toString(), token->getToken().size() == 0 ? "" : token->getToken().c_str());

		} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

		delete	token;
	}
}

void testSerializer(int argc, char** argv)
{
	if (argc < 4)
	{
		printUsage();
		exit(0);
	}

	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= document->createElement("document");
	document->appendChild(root);

	dom::Element *	child		= document->createElement("element");
	dom::Attr *	attr		= document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child				= document->createElement("element");
	root->appendChild(child);

	child				= document->createElement("element");
	child->setAttribute("attribute", "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text *	text		= document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child				= document->createElement("element");
	root->appendChild(child);

	//
	// Serialize
	//
	PrettyXMLSerializer	xmlSerializer(argv[2]);
	xmlSerializer.serialize(document);
	MinimalXMLSerializer	xmlSerializer2(argv[3]);
	xmlSerializer2.serialize(document);

	// delete Document and tree.
}

void testValidator(int argc, char** argv)
{
	if (argc < 3)
	{
		printUsage();
		exit(0);
	}

	//
	// Create tree of this document:
	// <? xml version="1.0" encoding="UTF-8"?>
	// <document>
	//   <element attribute="attribute value"/>
	//   <element/>
	//   <element attribute="attribute value" attribute2="attribute2 value">
	//     Element Value
	//   </element>
	//   <element>
	//   </element>
	// </document>
	//
	// Schema for this document:
	// document contains:  element
	// element contains:  element
	// element contains attributes:  attribute, attribute2
	//
	XMLValidator	xmlValidator;
	ValidChildren *	schemaElement	= xmlValidator.addSchemaElement("");
	schemaElement->addValidChild("document", false);
	schemaElement	= xmlValidator.addSchemaElement("document");
	schemaElement->addValidChild("element", false);
	schemaElement	= xmlValidator.addSchemaElement("element");
	schemaElement->addValidChild("element", false);
	schemaElement->addValidChild("attribute", true);
	schemaElement->addValidChild("attribute2", true);
	schemaElement->setCanHaveText(true);

	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= 0;
	dom::Element *	child		= 0;
	dom::Attr *	attr		= 0;

	if (xmlValidator.canRootElement("document"))
	{
		root		= document->createElement("document");
		document->appendChild(root);
	}
	else
	{
		printf("Attempted invalid schema operation.");
		exit(0);
	}

	if (xmlValidator.canAddElement(root, "element"))
	{
		child		= document->createElement("element");

		if (xmlValidator.canAddAttribute(child, "attribute"))
		{
			attr		= document->createAttribute("attribute");
			attr->setValue("attribute value");
			child->setAttributeNode(attr);
		}
		else
		{
			printf("Attempted invalid schema operation.");
			exit(0);
		}

		root->appendChild(child);
	}
	else
	{
		printf("Attempted invalid schema operation.");
		exit(0);
	}

	if (xmlValidator.canAddElement(root, "element"))
	{
		child			= document->createElement("element");
		root->appendChild(child);
	}
	else
	{
		printf("Attempted invalid schema operation.");
		exit(0);
	}

	if (xmlValidator.canAddElement(root, "element"))
	{
		child			= document->createElement("element");

		if (xmlValidator.canAddAttribute(child, "attribute"))
			child->setAttribute("attribute", "attribute value");
		else
		{
			printf("Attempted invalid schema operation.");
			exit(0);
		}

		if (xmlValidator.canAddAttribute(child, "attribute2"))
			child->setAttribute("attribute2", "attribute2 value");
		else
		{
			printf("Attempted invalid schema operation.");
			exit(0);
		}

		if (xmlValidator.canAddText(child))
		{
			dom::Text *	text		= document->createTextNode("Element Value");
			child->appendChild(text);
		}
		else
		{
			printf("Attempted invalid schema operation.");
			exit(0);
		}

		root->appendChild(child);
	}
	else
	{
		printf("Attempted invalid schema operation.");
		exit(0);
	}

	if (xmlValidator.canAddElement(root, "element"))
	{
		child			= document->createElement("element");
		root->appendChild(child);
	}
	else
	{
		printf("Attempted invalid schema operation.");
		exit(0);
	}

	//
	// Serialize
	//
	PrettyXMLSerializer	xmlSerializer(argv[2]);
	xmlSerializer.serialize(document);

	// delete Document and tree.
}

// Builder: Client
void testParser(int argc, char** argv)
{
	if (argc < 4)
	{
		printUsage();
		exit(0);
	}

	//
	// Director (XMLParser) drives the ConcreteBuilder (XMLDOMBuilder) which
	// uses the ConcreteFactory (StandardDOMNodeFactory) to create DOM nodes.
	// argv[2] = input XML file, argv[3] = output pretty-printed XML file.
	//
	StandardDOMNodeFactory	factory;
	XMLDOMBuilder		builder(&factory);
	XMLParser		parser(argv[2], &builder);

	parser.parse();

	dom::Document *		document	= builder.getDocument();

	PrettyXMLSerializer	serializer(argv[3]);
	serializer.serialize(document);
}
