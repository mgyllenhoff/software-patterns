#include "MinimalNodeProcessor.H"
#include "Document.H"
#include "Element.H"
#include "Attr.H"
#include "Text.H"

// Process Document node: extract version info and delegate to root element
void MinimalNodeProcessor::processDocument(dom::Document* node)
{
    file << "<? xml version=\"1.0\" encoding=\"UTF-8\"?>";
    processElement(node->getDocumentElement());
}

// Process Element node: extract tag name, attributes, and child nodes
void MinimalNodeProcessor::processElement(dom::Element* node)
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
        
        for (dom::NodeList::iterator i = node->getChildNodes()->begin();
             i != node->getChildNodes()->end();
             i++)
        {
            if (dynamic_cast<dom::Element*>(*i) != 0)
                processElement(dynamic_cast<dom::Element*>(*i));
            else if (dynamic_cast<dom::Text*>(*i) != 0)
                processText(dynamic_cast<dom::Text*>(*i));
        }
        
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