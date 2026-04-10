#include "XMLCommands.H"
#include "XMLSerializer.H"
#include "Element.H"

// Retrieve and validate that node at index is an ELEMENT_NODE
static dom::Element * resolveElement(AppContext & ctx, int index)
{
	if (!ctx.document)
	{
		printf("Error: no document loaded. Use 'parse <filename>' first.\n");
		return nullptr;
	}

	dom::Node * node = ctx.display.getNode(index);
	if (!node || node->getNodeType() != dom::Node::ELEMENT_NODE)
	{
		printf("Error: index %d is not an element node.\n", index);
		return nullptr;
	}

	return dynamic_cast<dom::Element *>(node);
}

// Refresh the display after a successful mutation
static void redisplay(AppContext & ctx)
{
	printf("\nCurrent XML Document:\n");
	printf("---------------------\n");
	ctx.display.display(ctx.document);
	printf("\n");
}

ParseCommand::ParseCommand(AppContext & ctx, const std::string & filename)
	: ctx(ctx), filename(filename) {}

void ParseCommand::execute()
{
	// Free any previously loaded document
	if (ctx.document)
	{
		delete ctx.document;
		ctx.document = nullptr;
	}

	ctx.document = ctx.loader.load(filename);

	if (!ctx.document)
	{
		printf("Error: could not open '%s'.\n", filename.c_str());
		return;
	}

	printf("Parsed '%s'.\n", filename.c_str());
	redisplay(ctx);
}

DisplayCommand::DisplayCommand(AppContext & ctx) : ctx(ctx) {}

void DisplayCommand::execute()
{
	if (!ctx.document)
	{
		printf("Error: no document loaded. Use 'parse <filename>' first.\n");
		return;
	}
	redisplay(ctx);
}

SerializeCommand::SerializeCommand(AppContext & ctx, Mode mode,
				   const std::string & filename)
	: ctx(ctx), mode(mode), filename(filename) {}

void SerializeCommand::execute()
{
	if (!ctx.document)
	{
		printf("Error: no document loaded. Use 'parse <filename>' first.\n");
		return;
	}

	XMLSerializer serializer(filename);
	if (mode == Mode::PRETTY)
		serializer.serializePretty(ctx.document);
	else
		serializer.serializeMinimal(ctx.document);

	printf("Serialized to '%s' (%s).\n",
	       filename.c_str(),
	       mode == Mode::PRETTY ? "pretty" : "minimal");
}

AddElementCommand::AddElementCommand(AppContext & ctx, int parentIndex,
				     const std::string & tagName)
	: ctx(ctx), parentIndex(parentIndex), tagName(tagName) {}

void AddElementCommand::execute()
{
	dom::Element * parent = resolveElement(ctx, parentIndex);
	if (!parent) return;

	if (tagName.empty())
	{
		printf("Error: tag name cannot be empty.\n");
		return;
	}

	dom::Element * newElem = ctx.editor.addElement(ctx.document, parent, tagName);
	if (!newElem)
		printf("Error: operation rejected by validator.\n");
	else
	{
		printf("Added <%s> as child of <%s>.\n",
		       tagName.c_str(), parent->getTagName().c_str());
		redisplay(ctx);
	}
}

RemoveElementCommand::RemoveElementCommand(AppContext & ctx, int index)
	: ctx(ctx), index(index) {}

void RemoveElementCommand::execute()
{
	dom::Element * elem = resolveElement(ctx, index);
	if (!elem) return;

	if (!ctx.editor.removeElement(elem))
		printf("Error: element has no parent (cannot remove document root).\n");
	else
	{
		printf("Removed <%s>.\n", elem->getTagName().c_str());
		redisplay(ctx);
	}
}

SetAttrCommand::SetAttrCommand(AppContext & ctx, int index,
			       const std::string & name, const std::string & value)
	: ctx(ctx), index(index), name(name), value(value) {}

void SetAttrCommand::execute()
{
	dom::Element * elem = resolveElement(ctx, index);
	if (!elem) return;

	if (name.empty())
	{
		printf("Error: attribute name cannot be empty.\n");
		return;
	}

	if (!ctx.editor.setAttribute(elem, name, value))
		printf("Error: attribute '%s' rejected by validator.\n", name.c_str());
	else
	{
		printf("Set @%s=\"%s\" on <%s>.\n",
		       name.c_str(), value.c_str(), elem->getTagName().c_str());
		redisplay(ctx);
	}
}

RemoveAttrCommand::RemoveAttrCommand(AppContext & ctx, int index,
				     const std::string & name)
	: ctx(ctx), index(index), name(name) {}

void RemoveAttrCommand::execute()
{
	dom::Element * elem = resolveElement(ctx, index);
	if (!elem) return;

	if (!ctx.editor.removeAttribute(elem, name))
		printf("Error: attribute '%s' not found on <%s>.\n",
		       name.c_str(), elem->getTagName().c_str());
	else
	{
		printf("Removed @%s from <%s>.\n",
		       name.c_str(), elem->getTagName().c_str());
		redisplay(ctx);
	}
}

AddTextCommand::AddTextCommand(AppContext & ctx, int index,
			       const std::string & text)
	: ctx(ctx), index(index), text(text) {}

void AddTextCommand::execute()
{
	dom::Element * elem = resolveElement(ctx, index);
	if (!elem) return;

	if (!ctx.editor.addText(ctx.document, elem, text))
		printf("Error: text content rejected by validator.\n");
	else
	{
		printf("Added text \"%s\" to <%s>.\n",
		       text.c_str(), elem->getTagName().c_str());
		redisplay(ctx);
	}
}

void HelpCommand::execute()
{
	printf("Commands:\n");
	printf("  parse <filename>                       Load and display an XML file\n");
	printf("  display                                Redisplay the current tree\n");
	printf("  serialize pretty <filename>            Write pretty-printed XML to file\n");
	printf("  serialize minimal <filename>           Write compact XML to file\n");
	printf("  add-element <index> <tag>              Add child element to node at index\n");
	printf("  remove-element <index>                 Remove element at index\n");
	printf("  set-attr <index> <name> <value>        Set attribute on element at index\n");
	printf("  remove-attr <index> <name>             Remove attribute from element at index\n");
	printf("  add-text <index> <text...>             Append text node to element at index\n");
	printf("  clone-subtree <src-index> <dst-index>  Deep-clone subtree and append to dst\n");
	printf("  help                                   Show this help\n");
	printf("  quit                                   Exit the interpreter\n\n");
}

CloneSubtreeCommand::CloneSubtreeCommand(AppContext & ctx,
					 int sourceIndex,
					 int targetParentIndex)
	: ctx(ctx), sourceIndex(sourceIndex), targetParentIndex(targetParentIndex) {}

void CloneSubtreeCommand::execute()
{
	if (!ctx.document)
	{
		printf("Error: no document loaded. Use 'parse <filename>' first.\n");
		return;
	}

	// Resolve source
	dom::Node * source = ctx.display.getNode(sourceIndex);
	if (!source)
	{
		printf("Error: index %d not found.\n", sourceIndex);
		return;
	}
	if (source->getNodeType() == dom::Node::DOCUMENT_NODE)
	{
		printf("Error: cannot clone the document root. Clone the document element instead.\n");
		return;
	}

	// Resolve target parent (must be an Element)
	dom::Element * targetParent = resolveElement(ctx, targetParentIndex);
	if (!targetParent) return;

	dom::Node * cloned = ctx.editor.cloneSubtree(source, targetParent);

	if (cloned)
	{
		printf("Cloned subtree (index %d) appended to <%s>.\n",
		       sourceIndex, targetParent->getTagName().c_str());
		redisplay(ctx);
	}
}
