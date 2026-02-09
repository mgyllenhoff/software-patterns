#include "PrettyNodeProcessor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

void PrettyNodeProcessor::prettyIndentation()
{
    for (int i = 0; i < indentationLevel; i++)
        file << "\t";
}

// Process Document open: emit XML declaration
void PrettyNodeProcessor::processDocumentOpen(dom::Document* node)
{
    file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    file << "\n";
}

// Process Document close: nothing to emit
void PrettyNodeProcessor::processDocumentClose(dom::Document* node)
{
}

// Process Element open: emit indented opening tag with attributes
void PrettyNodeProcessor::processElementOpen(dom::Element* node)
{
    prettyIndentation();
    file << "<" << node->getTagName();
    
    int attrCount = 0;
    
    for (dom::NamedNodeMap::iterator i = node->getAttributes()->begin();
         i != node->getAttributes()->end();
         i++)
    {
        processAttr(dynamic_cast<dom::Attr*>(*i));
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

// Process Element close: emit indented closing tag (only if element had children)
void PrettyNodeProcessor::processElementClose(dom::Element* node)
{
    if (node->getChildNodes()->size() > 0)
    {
        indentationLevel--;
        prettyIndentation();
        file << "</" << node->getTagName() << ">";
        file << "\n";
    }
}

// Process Attribute node: extract name and value
void PrettyNodeProcessor::processAttr(dom::Attr* node)
{
    file << " " << node->getName() << "=\"" << node->getValue() << "\"";
}

// Process Text node: extract text data with indentation
void PrettyNodeProcessor::processText(dom::Text* node)
{
    prettyIndentation();
    file << node->getData();
    file << "\n";
}