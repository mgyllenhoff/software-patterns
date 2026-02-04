#include "XMLSerializer.H"
#include "PrettyNodeProcessor.H"
#include "MinimalNodeProcessor.H"
#include "Document.H"
#include "Element.H"

// Helper method: delegates node processing to the given strategy
void XMLSerializer::serialize(dom::Node* node, NodeProcessor& processor)
{
    if (dynamic_cast<dom::Document*>(node) != 0)
        processor.processDocument(dynamic_cast<dom::Document*>(node));
    else if (dynamic_cast<dom::Element*>(node) != 0)
        processor.processElement(dynamic_cast<dom::Element*>(node));
}

// Creates and uses PrettyNodeProcessor strategy
void XMLSerializer::serializePretty(dom::Node* node)
{
    PrettyNodeProcessor processor(file);
    serialize(node, processor);
}

// Creates and uses MinimalNodeProcessor strategy
void XMLSerializer::serializeMinimal(dom::Node* node)
{
    MinimalNodeProcessor processor(file);
    serialize(node, processor);
}