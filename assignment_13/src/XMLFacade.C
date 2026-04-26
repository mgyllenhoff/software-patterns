#include "XMLFacade.H"

#include <stdio.h>
#include <fstream>
#include <iostream>

// Subsystem: DOM
#include "Document.H"
#include "Element.H"
#include "Text.H"
#include "Attr.H"
#include "NodeList.H"

// Subsystem: Tokenizer
#include "XMLTokenizer.H"

// Subsystem: Serialization
#include "PrettyXMLSerializer.H"
#include "MinimalXMLSerializer.H"

// Subsystem: Validation
#include "XMLValidator.H"

// Subsystem: Builder
#include "StandardDOMNodeFactory.H"
#include "XMLDOMBuilder.H"
#include "XMLParser.H"

// Subsystem: Flyweight
#include "DOMFlyweightFactory.H"

// Subsystem: Interpreter
#include "Expression.H"

static Expression * buildExpression(dom::Node * node)
{
	dom::Element * elem = dynamic_cast<dom::Element *>(node);
	if (elem == nullptr)
		return nullptr;

	const std::string & tag = elem->getTagName();

	if (tag == "value")
	{
		dom::NodeList * children = elem->getChildNodes();
		for (dom::NodeList::iterator i = children->begin(); i != children->end(); i++)
		{
			dom::Text * text = dynamic_cast<dom::Text *>(*i);
			if (text)
			{
				try { return new ValueExpression(std::stoi(text->getData())); }
				catch (...) {}
			}
		}
		return new ValueExpression(0);
	}

	if (tag == "operation")
	{
		const std::string & opStr	= elem->getAttribute("type");
		char		op		= opStr.empty() ? '+' : opStr[0];
		OperationExpression * expr	= new OperationExpression(op);

		dom::NodeList * children = elem->getChildNodes();
		for (dom::NodeList::iterator i = children->begin(); i != children->end(); i++)
		{
			Expression * child = buildExpression(*i);
			if (child)
				expr->addOperand(child);
		}
		return expr;
	}

	return nullptr;
}

XMLFacade::XMLFacade() {}

XMLFacade::~XMLFacade()
{
	// Release shared Flyweight pools for all subsystem clients
	DOMFlyweightFactory::clear();
}

// Subsystems: DOM, XMLTokenizer
void XMLFacade::tokenize(const std::vector<std::string> & files)
{
	// DOM node construction
	dom::Document *	document	= new Document_Impl;
	dom::Element *	element		= document->createElement("NewElement");
	dom::Text *	text		= document->createTextNode("Text Data");
	dom::Attr *	attr		= document->createAttribute("NewAttribute");

	printf("Element Tag = '%s'\n", element->getTagName().c_str());
	printf("Text Data = '%s'\n", text->getValue().c_str());
	printf("Attr Name = '%s'\n", attr->getName().c_str());

	element->setAttributeNode(attr);
	printf("Element attribute '%s'='%s'\n",
	  element->getTagName().c_str(), element->getAttribute("NewAttribute").c_str());

	delete element;
	delete text;
	delete attr;
	delete document;

	// Tokenize each file
	for (const std::string & filename : files)
	{
		XMLTokenizer		tokenizer(filename);
		XMLTokenizer::XMLToken *	token = 0;

		printf("File:  '%s'\n", filename.c_str());

		do
		{
			delete token;
			token = tokenizer.getNextToken();
			printf("\tLine %d:  %s = '%s'\n", tokenizer.getLineNumber(),
			  token->toString(),
			  token->getToken().size() == 0 ? "" : token->getToken().c_str());

		} while (token->getTokenType() != XMLTokenizer::XMLToken::NULL_TOKEN);

		delete token;
	}
}

// Subsystems: DOM, PrettyXMLSerializer, MinimalXMLSerializer
void XMLFacade::serialize(const std::string & prettyOut, const std::string & minimalOut)
{
	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= document->createElement("document");
	document->appendChild(root);

	dom::Element *	child		= document->createElement("element");
	dom::Attr *	attr		= document->createAttribute("attribute");
	attr->setValue("attribute value");
	child->setAttributeNode(attr);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	child = document->createElement("element");
	child->setAttribute("attribute",  "attribute value");
	child->setAttribute("attribute2", "attribute2 value");
	dom::Text * text = document->createTextNode("Element Value");
	child->appendChild(text);
	root->appendChild(child);

	child = document->createElement("element");
	root->appendChild(child);

	PrettyXMLSerializer	prettySerializer(prettyOut);
	prettySerializer.serialize(document);
	MinimalXMLSerializer	minimalSerializer(minimalOut);
	minimalSerializer.serialize(document);
}

// Subsystems: DOM, XMLValidator, PrettyXMLSerializer
void XMLFacade::validate(const std::string & prettyOut)
{
	XMLValidator		xmlValidator;
	ValidChildren *	schemaElement	= xmlValidator.addSchemaElement("");
	schemaElement->addValidChild("document", false);
	schemaElement	= xmlValidator.addSchemaElement("document");
	schemaElement->addValidChild("element", false);
	schemaElement	= xmlValidator.addSchemaElement("element");
	schemaElement->addValidChild("element", false);
	schemaElement->addValidChild("attribute",  true);
	schemaElement->addValidChild("attribute2", true);
	schemaElement->setCanHaveText(true);

	dom::Document *	document	= new Document_Impl;
	dom::Element *	root		= 0;
	dom::Element *	child		= 0;
	dom::Attr *	attr		= 0;

	if (xmlValidator.canRootElement("document"))
	{
		root = document->createElement("document");
		document->appendChild(root);
	}
	else { printf("Attempted invalid schema operation."); return; }

	if (xmlValidator.canAddElement(root, "element"))
	{
		child = document->createElement("element");
		if (xmlValidator.canAddAttribute(child, "attribute"))
		{
			attr = document->createAttribute("attribute");
			attr->setValue("attribute value");
			child->setAttributeNode(attr);
		}
		else { printf("Attempted invalid schema operation."); return; }
		root->appendChild(child);
	}
	else { printf("Attempted invalid schema operation."); return; }

	if (xmlValidator.canAddElement(root, "element"))
	{
		child = document->createElement("element");
		root->appendChild(child);
	}
	else { printf("Attempted invalid schema operation."); return; }

	if (xmlValidator.canAddElement(root, "element"))
	{
		child = document->createElement("element");

		if (xmlValidator.canAddAttribute(child, "attribute"))
			child->setAttribute("attribute",  "attribute value");
		else { printf("Attempted invalid schema operation."); return; }

		if (xmlValidator.canAddAttribute(child, "attribute2"))
			child->setAttribute("attribute2", "attribute2 value");
		else { printf("Attempted invalid schema operation."); return; }

		if (xmlValidator.canAddText(child))
		{
			dom::Text * text = document->createTextNode("Element Value");
			child->appendChild(text);
		}
		else { printf("Attempted invalid schema operation."); return; }

		root->appendChild(child);
	}
	else { printf("Attempted invalid schema operation."); return; }

	if (xmlValidator.canAddElement(root, "element"))
	{
		child = document->createElement("element");
		root->appendChild(child);
	}
	else { printf("Attempted invalid schema operation."); return; }

	PrettyXMLSerializer	xmlSerializer(prettyOut);
	xmlSerializer.serialize(document);
}

// Subsystems: XMLParser, XMLDOMBuilder, StandardDOMNodeFactory, Expression
void XMLFacade::interpret(const std::string & inputFile)
{
	StandardDOMNodeFactory	factory;
	XMLDOMBuilder		builder(&factory);
	XMLParser		parser(inputFile, &builder);
	parser.parse();

	dom::Document * document = builder.getDocument();

	Expression * root = buildExpression(document->getDocumentElement());
	if (!root)
	{
		printf("Could not build expression tree from '%s'\n", inputFile.c_str());
		return;
	}

	Context context;
	printf("Result: %d\n", root->interpret(context));

	delete root;
}
