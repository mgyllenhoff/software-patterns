#include "MinimalNodeProcessor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Process Document open: emit XML declaration
void MinimalNodeProcessor::processDocumentOpen(dom::Document* node)
{
    file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
}

// Process Document close: nothing to emit
void MinimalNodeProcessor::processDocumentClose(dom::Document* node)
{
}

// Process Element open: emit opening tag with attributes
// If the element has no children, emit self-closing tag
void MinimalNodeProcessor::processElementOpen(dom::Element* node)
{
    file << "<" << node->getTagName();
    
    for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
         i != node->getAttributes()->end();
         i++)
    {
        processAttr(dynamic_cast<dom::Attr*>(*i));
    }
    
    if (node->getChildNodes()->size() == 0)
    {
        file << "/>";
    }
    else
    {
        file << ">";
    }
}

// Process Element close: emit closing tag (only if element had children)
void MinimalNodeProcessor::processElementClose(dom::Element* node)
{
    if (node->getChildNodes()->size() > 0)
    {
        file << "</" << node->getTagName() << ">";
    }
}

// Process Attribute node: extract name and value
void MinimalNodeProcessor::processAttr(dom::Attr* node)
{
    file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}

// Process Text node: extract text data
void MinimalNodeProcessor::processText(dom::Text* node)
{
    file << node->getData();
}