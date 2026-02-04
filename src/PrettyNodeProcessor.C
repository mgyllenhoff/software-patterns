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

// Process Document node: extract version info and delegate to root element
void PrettyNodeProcessor::processDocument(dom::Document* node)
{
    file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    file << "\n";
    processElement(node->getDocumentElement());
}

// Process Element node: extract tag name, attributes, and child nodes
void PrettyNodeProcessor::processElement(dom::Element* node)
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
        
        for (dom::NodeList::iterator i = node->getChildNodes()->begin();
             i != node->getChildNodes()->end();
             i++)
        {
            if (dynamic_cast<dom::Element*>(*i) != 0)
                processElement(dynamic_cast<dom::Element*>(*i));
            else if (dynamic_cast<dom::Text*>(*i) != 0)
                processText(dynamic_cast<dom::Text*>(*i));
        }
        
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

// Process Text node: extract text data
void PrettyNodeProcessor::processText(dom::Text* node)
{
    prettyIndentation();
    file << node->getData();
    file << "\n";
}