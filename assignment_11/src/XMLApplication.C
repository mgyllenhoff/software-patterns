#include "XMLApplication.H"
#include "AppContext.H"
#include "Invoker.H"

// An empty XMLValidator schema means every canAdd* call returns true, so all edit operations are allowed
XMLApplication::XMLApplication(void)
	: document(nullptr), editor(validator) {}

XMLApplication::~XMLApplication(void)
{
	delete document;
}

// Load, display, then loop on user commands
void XMLApplication::run(const std::string & inputFile,
			  const std::string & outFile)
{
	outputFile = outFile;

	printf("\nXML Display & Editing Application\n");
	printf("---------------------------------\n");
	printf("  Input : %s\n", inputFile.c_str());
	printf("  Output: %s\n\n", outputFile.c_str());

	// Layer 3: load document
	document = loader.load(inputFile);
	if (!document)
	{
		printf("Error: could not open '%s'\n", inputFile.c_str());
		return;
	}

	redraw();

	bool running = true;
	while (running)
	{
		printMenu();
		int choice = readInt("Choice: ");

		switch (choice)
		{
		case 1: redraw();			break;
		case 2: handleAddElement();		break;
		case 3: handleRemoveElement();		break;
		case 4: handleSetAttribute();		break;
		case 5: handleRemoveAttribute();	break;
		case 6: handleAddText();		break;
		case 7:
			editor.save(document, outputFile);
			printf("Saved to %s\n\n", outputFile.c_str());
			break;
		case 8:
			running = false;
			break;
		default:
			printf("Unknown command.\n\n");
			break;
		}
	}

	printf("Goodbye.\n");
}

void XMLApplication::printMenu(void)
{
	printf("Commands:\n");
	printf("  1) Display tree\n");
	printf("  2) Add child element\n");
	printf("  3) Remove element\n");
	printf("  4) Set attribute\n");
	printf("  5) Remove attribute\n");
	printf("  6) Add text node\n");
	printf("  7) Save to file\n");
	printf("  8) Quit\n");
}

// Render the current document tree via XMLDisplay (Layer 4 peer)
void XMLApplication::redraw(void)
{
	printf("\nCurrent XML Document:\n");
	printf("---------------------\n");
	display.display(document);
	printf("\n");
}

// Input helpers
int XMLApplication::readInt(const char * prompt)
{
	printf("%s", prompt);
	int v = 0;
	scanf("%d", &v);
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
	return v;
}

void XMLApplication::readLine(const char * prompt, std::string & out)
{
	printf("%s", prompt);
	char buf[256] = {};
	if (fgets(buf, sizeof(buf), stdin))
	{
		out = buf;
		if (!out.empty() && out.back() == '\n')
			out.pop_back();
	}
	else
	{
		out.clear();
	}
}

// Ask user for parent index + tag name, call XMLEditor
void XMLApplication::handleAddElement(void)
{
	int parentIdx = readInt("Parent element index: ");
	dom::Node * parentNode = display.getNode(parentIdx);

	if (!parentNode || parentNode->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n\n", parentIdx);
		return;
	}

	std::string tagName;
	readLine("New element tag name: ", tagName);
	if (tagName.empty())
	{
		printf("Error: tag name cannot be empty.\n\n");
		return;
	}

	dom::Element * parent  = dynamic_cast<dom::Element *>(parentNode);
	dom::Element * newElem = editor.addElement(document, parent, tagName);

	if (!newElem)
		printf("Error: operation rejected by validator.\n\n");
	else
	{
		printf("Added <%s> as child of <%s>.\n\n",
		  tagName.c_str(), parent->getTagName().c_str());
		redraw();
	}
}

// Ask user for element index, call XMLEditor
void XMLApplication::handleRemoveElement(void)
{
	int idx = readInt("Element index to remove: ");
	dom::Node * node = display.getNode(idx);

	if (!node || node->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n\n", idx);
		return;
	}

	dom::Element * elem = dynamic_cast<dom::Element *>(node);
	if (!editor.removeElement(elem))
		printf("Error: element has no parent (cannot remove document root).\n\n");
	else
	{
		printf("Removed <%s>.\n\n", elem->getTagName().c_str());
		redraw();
	}
}

// Ask user for element index, attribute name, and value
void XMLApplication::handleSetAttribute(void)
{
	int idx = readInt("Element index: ");
	dom::Node * node = display.getNode(idx);

	if (!node || node->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n\n", idx);
		return;
	}

	std::string attrName, attrValue;
	readLine("Attribute name: ",  attrName);
	readLine("Attribute value: ", attrValue);

	if (attrName.empty())
	{
		printf("Error: attribute name cannot be empty.\n\n");
		return;
	}

	dom::Element * elem = dynamic_cast<dom::Element *>(node);
	if (!editor.setAttribute(elem, attrName, attrValue))
		printf("Error: attribute '%s' rejected by validator.\n\n", attrName.c_str());
	else
	{
		printf("Set @%s=\"%s\" on <%s>.\n\n",
		  attrName.c_str(), attrValue.c_str(), elem->getTagName().c_str());
		redraw();
	}
}

void XMLApplication::handleRemoveAttribute(void)
{
	int idx = readInt("Element index: ");
	dom::Node * node = display.getNode(idx);

	if (!node || node->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n\n", idx);
		return;
	}

	std::string attrName;
	readLine("Attribute name to remove: ", attrName);

	dom::Element * elem = dynamic_cast<dom::Element *>(node);
	if (!editor.removeAttribute(elem, attrName))
		printf("Error: attribute '%s' not found on <%s>.\n\n",
		  attrName.c_str(), elem->getTagName().c_str());
	else
	{
		printf("Removed @%s from <%s>.\n\n",
		  attrName.c_str(), elem->getTagName().c_str());
		redraw();
	}
}

// Command Pattern: Client
// Wire Receivers into AppContext, hand it to the Invoker, and start the loop.
void XMLApplication::runInvoker()
{
	printf("\nXML Command Interpreter\n");
	printf("-----------------------\n");
	printf("Type 'help' for a list of commands.\n\n");

	AppContext ctx(document, loader, editor, display);
	Invoker invoker(ctx);
	invoker.run();

	printf("Goodbye.\n");
}

void XMLApplication::handleAddText(void)
{
	int idx = readInt("Element index: ");
	dom::Node * node = display.getNode(idx);

	if (!node || node->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n\n", idx);
		return;
	}

	std::string text;
	readLine("Text content: ", text);

	dom::Element * elem = dynamic_cast<dom::Element *>(node);
	if (!editor.addText(document, elem, text))
		printf("Error: text content rejected by validator.\n\n");
	else
	{
		printf("Added text node \"%s\" to <%s>.\n\n",
		  text.c_str(), elem->getTagName().c_str());
		redraw();
	}
}
