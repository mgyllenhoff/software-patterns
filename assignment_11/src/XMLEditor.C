#include "XMLEditor.H"
#include "Text.H"			// Layer 2
#include "XMLSerializer.H"	// Layer 1

dom::Element * XMLEditor::addElement(dom::Document * doc,
				     dom::Element  * parent,
				     const std::string & tagName)
{
	// Validate against schema before mutating the Domain Layer
	if (!validator.canAddElement(parent, tagName))
		return nullptr;

	dom::Element * newElem = doc->createElement(tagName);
	parent->appendChild(newElem);
	return newElem;
}

bool XMLEditor::removeElement(dom::Element * element)
{
	dom::Node * parent = element->getParentNode();
	if (!parent)
		return false;	// If root or unattached, cannot remove

	parent->removeChild(element);
	return true;
}

bool XMLEditor::setAttribute(dom::Element  * element,
			     const std::string & name,
			     const std::string & value)
{
	if (!validator.canAddAttribute(element, name))
		return false;

	element->setAttribute(name, value);
	return true;
}

bool XMLEditor::removeAttribute(dom::Element * element, const std::string & name)
{
	if (!element->hasAttribute(name))
		return false;

	element->removeAttribute(name);
	return true;
}

bool XMLEditor::addText(dom::Document * doc,
			dom::Element  * element,
			const std::string & text)
{
	if (!validator.canAddText(element))
		return false;

	dom::Text * textNode = doc->createTextNode(text);
	element->appendChild(textNode);
	return true;
}

// Save delegates to XMLSerializer (Layer 1)
void XMLEditor::save(dom::Document * doc, const std::string & filename)
{
	XMLSerializer serializer(filename);
	serializer.serializePretty(doc);
}

dom::Node * XMLEditor::cloneSubtree(dom::Node * source, dom::Element * targetParent)
{
	dom::Node * cloned = source->clone();
	targetParent->appendChild(cloned);
	return cloned;
}
