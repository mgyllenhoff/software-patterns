#include "XMLSerializer.H"
#include "PrettyNodeProcessor.H"
#include "MinimalNodeProcessor.H"
#include "DOMIterator.H"
#include "Document.H"
#include "Element.H"
#include "Text.H"

// Strategy Pattern 1 (Node Processing):
//  Context uses an Iterator to traverse the DOM tree and dispatches ENTERING/LEAVING events to the Strategy (NodeProcessor)
//  The Context does not know which ConcreteStrategy it is using
void XMLSerializer::serialize(dom::Node* node, NodeProcessor& processor)
{
    DOMIterator * it = node->createIterator();

    for (it->first(); !it->isDone(); it->next())
    {
        dom::Node * current = it->currentItem();

        if (it->currentEvent() == DOMIterator::ENTERING)
        {
            if (dynamic_cast<dom::Document*>(current) != 0)
                processor.processDocumentOpen(dynamic_cast<dom::Document*>(current));
            else if (dynamic_cast<dom::Element*>(current) != 0)
                processor.processElementOpen(dynamic_cast<dom::Element*>(current));
            else if (dynamic_cast<dom::Text*>(current) != 0)
                processor.processText(dynamic_cast<dom::Text*>(current));
        }
        else // LEAVING
        {
            if (dynamic_cast<dom::Document*>(current) != 0)
                processor.processDocumentClose(dynamic_cast<dom::Document*>(current));
            else if (dynamic_cast<dom::Element*>(current) != 0)
                processor.processElementClose(dynamic_cast<dom::Element*>(current));
        }
    }

    delete it;
}

// Client selects ConcreteStrategy: PrettyNodeProcessor
void XMLSerializer::serializePretty(dom::Node* node)
{
    PrettyNodeProcessor processor(output); // ConcreteStrategy
    serialize(node, processor); // Context uses Strategy
}

// Client selects ConcreteStrategy: MinimalNodeProcessor
void XMLSerializer::serializeMinimal(dom::Node* node)
{
    MinimalNodeProcessor processor(output); // ConcreteStrategy
    serialize(node, processor); // Context uses Strategy
}