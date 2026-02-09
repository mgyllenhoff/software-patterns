#ifndef PRETTYNODEPROCESSOR_H
#define PRETTYNODEPROCESSOR_H

#include "NodeProcessor.H"
#include <ostream>

// Strategy Pattern 1 (Node Processing): ConcreteStrategy
class PrettyNodeProcessor : public NodeProcessor
{
private:
    std::ostream& file;
    int indentationLevel;
    
    void prettyIndentation();
    
public:
    PrettyNodeProcessor(std::ostream& out) : file(out), indentationLevel(0) {}
    virtual ~PrettyNodeProcessor() {}
    
    virtual void processDocumentOpen(dom::Document* doc);
    virtual void processDocumentClose(dom::Document* doc);
    virtual void processElementOpen(dom::Element* elem);
    virtual void processElementClose(dom::Element* elem);
    virtual void processAttr(dom::Attr* attr);
    virtual void processText(dom::Text* text);
};

#endif