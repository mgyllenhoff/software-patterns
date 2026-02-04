#ifndef PRETTYNODEPROCESSOR_H
#define PRETTYNODEPROCESSOR_H

#include "NodeProcessor.H"
#include <ostream>

// ConcreteStrategy
class PrettyNodeProcessor : public NodeProcessor
{
private:
    std::ostream& file;
    int indentationLevel;
    
    void prettyIndentation();
    
public:
    PrettyNodeProcessor(std::ostream& out) : file(out), indentationLevel(0) {}
    virtual ~PrettyNodeProcessor() {}
    
    virtual void processDocument(dom::Document* doc);
    virtual void processElement(dom::Element* elem);
    virtual void processAttr(dom::Attr* attr);
    virtual void processText(dom::Text* text);
};

#endif