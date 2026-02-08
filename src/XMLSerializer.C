#include "XMLSerializer.H"
#include "PrettyNodeProcessor.H"
#include "MinimalNodeProcessor.H"
#include "Document.H"
#include "Element.H"

// Strategy Pattern 1 (Node Processing):
//  Context dispatches to the Strategy (NodeProcessor) based on node type
//  The Context does not know which ConcreteStrategy it is using
void XMLSerializer::serialize(dom::Node* node, NodeProcessor& processor)
{
    if (dynamic_cast<dom::Document*>(node) != 0)
        processor.processDocument(dynamic_cast<dom::Document*>(node));
    else if (dynamic_cast<dom::Element*>(node) != 0)
        processor.processElement(dynamic_cast<dom::Element*>(node));
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