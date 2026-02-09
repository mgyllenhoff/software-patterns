#ifndef MINIMALNODEPROCESSOR_H
#define MINIMALNODEPROCESSOR_H

#include "NodeProcessor.H"
#include <ostream>

// Strategy Pattern 1 (Node Processing): ConcreteStrategy
class MinimalNodeProcessor : public NodeProcessor
{
private:
    std::ostream& file;
    
public:
    MinimalNodeProcessor(std::ostream& out) : file(out) {}
    virtual ~MinimalNodeProcessor() {}

    virtual void processDocumentOpen(dom::Document* doc);
    virtual void processDocumentClose(dom::Document* doc);
    virtual void processElementOpen(dom::Element* elem);
    virtual void processElementClose(dom::Element* elem);
    virtual void processAttr(dom::Attr* attr);
    virtual void processText(dom::Text* text);
};

#endif