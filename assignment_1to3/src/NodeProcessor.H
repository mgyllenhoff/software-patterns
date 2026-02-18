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

// Strategy Pattern 1 (Node Processing): Strategy Interface
class NodeProcessor
{
public:
    virtual ~NodeProcessor() {}

    // Document events
    virtual void processDocumentOpen(dom::Document* doc) = 0;
    virtual void processDocumentClose(dom::Document* doc) = 0;

    // Element events
    virtual void processElementOpen(dom::Element* elem) = 0;
    virtual void processElementClose(dom::Element* elem) = 0;

    // Leaf node events (no open/close distinction needed)
    virtual void processAttr(dom::Attr* attr) = 0;
    virtual void processText(dom::Text* text) = 0;
};

#endif