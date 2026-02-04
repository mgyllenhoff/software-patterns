#ifndef NODEPROCESSOR_H
#define NODEPROCESSOR_H

#include "Node.H"

namespace dom
{
    class Document;
    class Element;
    class Attr;
    class Text;
}

// Strategy Interface
class NodeProcessor
{
public:
    virtual ~NodeProcessor() {}
    
    // Methods for processing each node type
    virtual void processDocument(dom::Document* doc) = 0;
    virtual void processElement(dom::Element* elem) = 0;
    virtual void processAttr(dom::Attr* attr) = 0;
    virtual void processText(dom::Text* text) = 0;
};

#endif