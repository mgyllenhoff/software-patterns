#include <stdio.h>
#include "Attr.H"
#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "XMLTokenizer.H"
#include "XMLSerializer.H"
#include "XMLValidator.H"

void testTokenizer(int argc, char** argv);
void testSerializer(int argc, char** argv);
void testValidator(int argc, char** argv);
void testChainOfResponsibility(void);
void testMemento(void);

void printUsage(void)
{
	printf("Usage:\n");
	printf("\tTest t [file] ...\n");
	printf("\tTest s [file1] [file2]\n");
	printf("\tTest v [file]\n");
	printf("\tTest c\n");
	printf("\tTest m\n");
}

int main(int argc, char** argv)
{
	if (argc < 2)
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
	case 'C':
	case 'c':
		testChainOfResponsibility();
		break;
	case 'M':
	case 'm':
		testMemento();
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
	XMLSerializer	xmlSerializer(argv[2]);
	xmlSerializer.serializePretty(document);
	XMLSerializer	xmlSerializer2(argv[3]);
	xmlSerializer2.serializeMinimal(document);

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
	XMLSerializer	xmlSerializer(argv[2]);
	xmlSerializer.serializePretty(document);

	// delete Document and tree.
}

// Chain of Responsibility: Client
void testChainOfResponsibility(void)
{
	//
	// Build DOM tree matching this XML config:
	// <handlers>
	//   <handler message="type1">
	//     <handler message="type2"/>
	//     <handler message="type2"/>
	//   </handler>
	// </handlers>
	//
	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= document->createElement("handlers");
	document->appendChild(root);

	dom::Element *	parent		= document->createElement("handler");
	parent->setAttribute("message", "type1");
	root->appendChild(parent);

	dom::Element *	child1		= document->createElement("handler");
	child1->setAttribute("message", "type2");
	parent->appendChild(child1);

	dom::Element *	child2		= document->createElement("handler");
	child2->setAttribute("message", "type2");
	parent->appendChild(child2);

	//
	// Fire events at child1 and chain propagates up to parent if needed
	//
	printf("Sending 'type2' to child1:\n\t");
	child1->handleRequest("type2");		// child1 handles it directly

	printf("Sending 'type1' to child1:\n\t");
	child1->handleRequest("type1");		// child1 can't handle, so passes to parent

	printf("Sending 'type3' to child1:\n\t");
	child1->handleRequest("type3");		// nobody handles it

	// delete Document and tree.
}

// Memento: Caretaker
void testMemento(void)
{
	//
	// Configure Schema A: <document> contains <element>
	//   (one part of the application sets up this validator)
	//
	XMLValidator	validator;
	ValidChildren *	sc	= validator.addSchemaElement("");
	sc->addValidChild("document", false);
	sc	= validator.addSchemaElement("document");
	sc->addValidChild("element", false);
	sc	= validator.addSchemaElement("element");
	sc->addValidChild("attribute", true);
	sc->setCanHaveText(true);

	printf("--- Schema A (document/element) ---\n");
	printf("  Can root 'document': %s\n", validator.canRootElement("document") ? "yes" : "no");
	printf("  Can root 'report':   %s\n", validator.canRootElement("report")   ? "yes" : "no");

	// Caretaker saves the Originator's state before handing the
	// validator off to another part of the application
	XMLValidatorMemento *	memento	= validator.CreateMemento();

	//
	// A different part of the application reconfigures the same
	// validator for an entirely different schema: <report> contains <section>
	//
	printf("\n--- Schema B (report/section) ---\n");
	sc	= validator.addSchemaElement("");
	sc->addValidChild("report", false);
	sc	= validator.addSchemaElement("report");
	sc->addValidChild("section", false);

	printf("  Can root 'document': %s\n", validator.canRootElement("document") ? "yes" : "no");
	printf("  Can root 'report':   %s\n", validator.canRootElement("report")   ? "yes" : "no");

	// Caretaker hands the Memento back to the Originator to undo
	// the reconfiguration and return to the original schema
	printf("\n--- Restored Schema A from Memento ---\n");
	validator.SetMemento(memento);

	printf("  Can root 'document': %s\n", validator.canRootElement("document") ? "yes" : "no");
	printf("  Can root 'report':   %s\n", validator.canRootElement("report")   ? "yes" : "no");

	delete memento;
}