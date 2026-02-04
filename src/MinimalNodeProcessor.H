#ifndef MINIMALNODEPROCESSOR_H
#define MINIMALNODEPROCESSOR_H

#include "NodeProcessor.H"
#include <ostream>

// ConcreteStrategy
class MinimalNodeProcessor : public NodeProcessor
{
private:
    std::ostream& file;
    
public:
    MinimalNodeProcessor(std::ostream& out) : file(out) {}
    virtual ~MinimalNodeProcessor() {}
    
    virtual void processDocument(dom::Document* doc);
    virtual void processElement(dom::Element* elem);
    virtual void processAttr(dom::Attr* attr);
    virtual void processText(dom::Text* text);
};

#endif